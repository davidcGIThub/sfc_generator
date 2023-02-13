#include "SFCMapCreator.hpp"

SFCMapCreator::SFCMapCreator(std::pair<float,float> x_bounds,
                      std::pair<float,float> y_bounds,
                      std::list<obstacle> obstacle_list):
                      _x_bounds(x_bounds), _y_bounds(y_bounds),
                      _obstacle_list(obstacle_list){}

std::list<sfc> SFCMapCreator::createSFCMap()
{

}
    
void SFCMapCreator::createSFCsForObstacle(obstacle obst)
{

}

void SFCMapCreator::createSFCsAtFace(unsigned int obstacle_index, std::string face)
{
    // make list of obstacles
    // remove obstacles to on the other side of starting obstacle
    // find closest obstacle in a direction --> then remove obstacles behind it
    // do this for all directions
}

void SFCMapCreator::OrganizeObstacles()
{

}

void SFCMapCreator::OrganizeObstaclesByLeftFace()
{

}

