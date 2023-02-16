#include "SFCMapCreator.hpp"

SFCMapCreator::SFCMapCreator(float min_spacing, float x_max,
                      float y_max, float x_min, float y_min,
                      unsigned int num_obstacles, float obstacle_array[]):
                      _min_spacing(min_spacing), 
                      _x_bounds(std::pair<float,float>(x_min,x_max)), 
                      _y_bounds(std::pair<float,float>(y_min,y_max)),
                      _num_obstacles(num_obstacles)
{
    _obstacle_list = convertObstacleArrayToVector(obstacle_array);
    _left_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "left");
    _right_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "right");
    _top_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "top");
    _bottom_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "bottom");
    createSFCs();
}

SFCMapCreator::SFCMapCreator(float min_spacing, float x_max,
                      float y_max, float x_min, float y_min,
                      unsigned int num_obstacles, std::vector<Obstacle::Box> obstacle_list):
                      _min_spacing(min_spacing), 
                      _x_bounds(std::pair<float,float>(x_min,x_max)), 
                      _y_bounds(std::pair<float,float>(y_min,y_max)),
                      _num_obstacles(num_obstacles), _obstacle_list(obstacle_list)
{
    _left_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "left");
    _right_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "right");
    _top_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "top");
    _bottom_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "bottom");
    createSFCs();
}

unsigned int SFCMapCreator::getNumberOfSFCs()
{
    return _sfc_list.size();
}

float* SFCMapCreator::getSFCArray()
{
    unsigned int number_of_sfcs = getNumberOfSFCs();
    float* sfc_array = new float[number_of_sfcs*4];
    unsigned int count{0};
    for(auto sfc: _sfc_list)
    {
        sfc_array[count] = sfc.x_max;
        sfc_array[count+number_of_sfcs] = sfc.y_max;
        sfc_array[count+2*number_of_sfcs] = sfc.x_min;
        sfc_array[count+3*number_of_sfcs] = sfc.y_min;
        count++;
    }
    return sfc_array;
}

void SFCMapCreator::printSFCs()
{
    unsigned int count{0};
    for(auto sfc: _sfc_list)
    {
        std::cout << "SFC 1: (x_max, y_max) = (" << sfc.x_max << "," << sfc.y_max 
            <<  ") , (x_min, y_min) = (" << sfc.x_min << "," << sfc.y_min << ")"
    }

}

std::vector<Obstacle::Box> SFCMapCreator::convertObstacleArrayToVector(float obstacle_array[])
{
    std::vector<Obstacle::Box> obstacle_list;
    for(unsigned int i; i < _num_obstacles; i++)
    {
        float max_x = obstacle_array[i];
        float max_y = obstacle_array[i + _num_obstacles];
        float min_x = obstacle_array[i + _num_obstacles*2];
        float min_y = obstacle_array[i + _num_obstacles*3];
        Obstacle::Box box{max_x, max_y, min_x, min_y};
        obstacle_list.push_back(box);
    }
    return obstacle_list;
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

