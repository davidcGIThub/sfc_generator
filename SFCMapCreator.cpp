#include "SFCMapCreator.hpp"

SFCMapCreator::SFCMapCreator(float min_spacing,
                      std::pair<float,float> x_bounds,
                      std::pair<float,float> y_bounds,
                      std::vector<Obstacle::Box> obstacle_list):
                      _min_spacing(min_spacing), _x_bounds(x_bounds), _y_bounds(y_bounds),
                      _obstacle_list(obstacle_list)
{
    _left_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "left");
    _right_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "right");
    _top_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "top");
    _bottom_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "bottom");
    _num_obstacles = obstacle_list.size();
    createSFCs();
}

std::set<SFC> SFCMapCreator::getSFCMap()
{
    return _sfc_list;
}

void SFCMapCreator::createSFCs()
{
    for(unsigned int i=0; i<_num_obstacles; i++)
    {
        createBottomSFC(i);
        createTopSFC(i);
        createLeftSFC(i);
        createRightSFC(i);
    }
}
    
void SFCMapCreator::createRightSFC(unsigned int &ordered_index)
{
    float max_x{_x_bounds.second};
    float max_y{_y_bounds.second};
    float min_x{_x_bounds.first};
    float min_y{_y_bounds.first};
    unsigned int obstacle_index = _right_face_orderd_indices[ordered_index];
    float start_x = _obstacle_list[obstacle_index].max_x;
    float start_y = (_obstacle_list[obstacle_index].max_y + _obstacle_list[obstacle_index].min_y)/2.0;
    min_x = start_x;
    for(unsigned int i = ordered_index+1; i++; i<_num_obstacles)
    {
        unsigned int index = _right_face_orderd_indices[i];
        float obstacle_top = _obstacle_list[index].max_y;
        float obstacle_bottom = _obstacle_list[index].min_y;
        if(obstacle_top < start_y && obstacle_top >= min_y)
        {
            min_y = obstacle_top;
        }
        else if(obstacle_bottom > start_y && obstacle_top < max_y)
        {
            max_y = obstacle_bottom;
        }
        else if(obstacle_top > start_y && obstacle_bottom < start_y)
        {
            float obstacle_left = _obstacle_list[index].min_x;
            max_x = obstacle_left;
            break;
        }
    }
    SFC sfc{max_x,max_y,min_x,min_y};
    _sfc_list.insert(sfc);
}

void SFCMapCreator::createLeftSFC(unsigned int &ordered_index)
{
    float max_x{_x_bounds.second};
    float max_y{_y_bounds.second};
    float min_x{_x_bounds.first};
    float min_y{_y_bounds.first};
    unsigned int obstacle_index = _left_face_orderd_indices[ordered_index];
    float start_x = _obstacle_list[obstacle_index].min_x;
    float start_y = (_obstacle_list[obstacle_index].max_y + _obstacle_list[obstacle_index].min_y)/2.0;
    max_x = start_x;
    for(unsigned int i = ordered_index+1; i++; i<_num_obstacles)
    {
        unsigned int index = _left_face_orderd_indices[i];
        float obstacle_top = _obstacle_list[index].max_y;
        float obstacle_bottom = _obstacle_list[index].min_y;
        if(obstacle_top < start_y && obstacle_top >= min_y)
        {
            min_y = obstacle_top;
        }
        else if(obstacle_bottom > start_y && obstacle_top < max_y)
        {
            max_y = obstacle_bottom;
        }
        else if(obstacle_top > start_y && obstacle_bottom < start_y)
        {
            float obstacle_right = _obstacle_list[index].max_x;
            min_x = obstacle_right;
            break;
        }
    }
    SFC sfc{max_x,max_y,min_x,min_y};
    _sfc_list.insert(sfc);
}

void SFCMapCreator::createTopSFC(unsigned int &ordered_index)
{
    float max_x{_x_bounds.second};
    float max_y{_y_bounds.second};
    float min_x{_x_bounds.first};
    float min_y{_y_bounds.first};
    unsigned int obstacle_index = _top_face_orderd_indices[ordered_index];
    float start_x = (_obstacle_list[obstacle_index].max_x + _obstacle_list[obstacle_index].min_x)/2.0;
    float start_y = _obstacle_list[obstacle_index].max_y;
    min_y = start_y;
    for(unsigned int i = ordered_index+1; i++; i<_num_obstacles)
    {
        unsigned int index = _top_face_orderd_indices[i];
        float obstacle_right_side = _obstacle_list[index].max_x;
        float obstacle_left_side = _obstacle_list[index].min_x;
        if(obstacle_right_side < start_x && obstacle_right_side >= min_x)
        {
            min_x = obstacle_right_side;
        }
        else if(obstacle_left_side > start_x && obstacle_left_side < max_x)
        {
            max_x = obstacle_left_side;
        }
        else if(obstacle_right_side > start_x && obstacle_left_side < start_x)
        {
            float obstacle_bottom = _obstacle_list[index].min_y;
            max_y = obstacle_bottom;
            break;
        }
    }
    SFC sfc{max_x,max_y,min_x,min_y};
    _sfc_list.insert(sfc);
}

void SFCMapCreator::createBottomSFC(unsigned int &ordered_index)
{
    float max_x{_x_bounds.second};
    float max_y{_y_bounds.second};
    float min_x{_x_bounds.first};
    float min_y{_y_bounds.first};
    unsigned int obstacle_index = _bottom_face_orderd_indices[ordered_index];
    float start_x = (_obstacle_list[obstacle_index].max_x + _obstacle_list[obstacle_index].min_x)/2.0;
    float start_y = _obstacle_list[obstacle_index].min_y;
    max_y = start_y;
    for(unsigned int i = ordered_index+1; i++; i<_num_obstacles)
    {
        unsigned int index = _bottom_face_orderd_indices[i];
        float obstacle_right_side = _obstacle_list[index].max_x;
        float obstacle_left_side = _obstacle_list[index].min_x;
        if(obstacle_right_side < start_x && obstacle_right_side >= min_x)
        {
            min_x = obstacle_right_side;
        }
        else if(obstacle_left_side > start_x && obstacle_left_side < max_x)
        {
            max_x = obstacle_left_side;
        }
        else if(obstacle_right_side > start_x && obstacle_left_side < start_x)
        {
            float obstacle_top = _obstacle_list[index].max_y;
            min_y = obstacle_top;
            break;
        }
    }
    SFC sfc{max_x,max_y,min_x,min_y};
    _sfc_list.insert(sfc);
}

