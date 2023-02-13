#include "SFCMapCreator.hpp"

SFCMapCreator::SFCMapCreator(std::pair<float,float> x_bounds,
                      std::pair<float,float> y_bounds,
                      std::vector<Obstacle::Box> obstacle_list):
                      _x_bounds(x_bounds), _y_bounds(y_bounds),
                      _obstacle_list(obstacle_list)
{
    _left_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "left");
    _right_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "right");
    _top_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "top");
    _bottom_face_orderd_indices = Obstacle::sortBoxIndices(_obstacle_list, "bottom");
}

std::vector<Sfc> SFCMapCreator::createSFCMap()
{

}
    
void SFCMapCreator::createSFCsForObstacle(Obstacle::Box obst)
{

}

void createSFC(std::pair<float,float> &start_coordinates, 
                std::pair<float,float> &start_obstacle_direction)
{
    // make list of obstacles
    // remove obstacles to on the other side of starting obstacle
    // find closest obstacle in a direction --> then remove obstacles behind it
    // do this for all directions
}

