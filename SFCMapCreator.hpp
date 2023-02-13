#ifndef SFCMAPCREATOR_HPP
#define SFCMAPCREATOR_HPP

#include <list>
#include <string>
#include "Obstacle.hpp"

struct Sfc
{
    float x_center;
    float y_center;
    float width;
    float height;
    std::list<std::pair<float,float>> node_id; 
};

class SFCMapCreator
{
    public:
        SFCMapCreator(std::pair<float,float> x_bounds,
                      std::pair<float,float> y_bounds,
                      std::list<Obstacle> obstacle_list);
        std::list<Sfc> createSFCMap();
    
    private:
        std::pair<float,float> _x_bounds;
        std::pair<float,float> _y_bounds;
        std::list<Obstacle> _obstacle_list;
        std::list<Obstacle> _obstacle_list;
        std::list<Obstacle> _obstacle_list;
        void createSFCsForObstacle(Obstacle obst);
        void createSFC(std::pair<float,float> &start_coordinates, 
                        std::pair<float,float> &start_obstacle_direction);
        void SFCMapCreator::OrganizeObstacles();
        void SFCMapCreator::OrganizeObstaclesByLeftFace();
}

#endif



// #include <iostream>
// #include <map>
// // #include <pair>

// int main()
// {
//   // Create a map of strings to integers
//   std::map<std::pair<int,int>, int> map;
 
//   // Insert some values into the map
//   std::pair<int,int> pair1(10,11);
//   std::pair<int,int> pair2(11,21);
//   std::pair<int,int> pair3(10,11);
//   map[pair1] = 1;
//   map[pair2] = 2;
//   map[pair3] = 3;
 
//   // Get an iterator pointing to the first element in the map
//   std::map<std::pair<int,int>, int>::iterator it = map.begin();
 
//   // Iterate through the map and print the elements
//   while (it != map.end())
//   {
//     std::cout << "Key: " << it->first.first << it->first.second << ", Value: " << it->second << std::endl;
//     ++it;
//   }
 
//   return 0;
// }