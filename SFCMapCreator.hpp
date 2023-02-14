#ifndef SFCMAPCREATOR_HPP
#define SFCMAPCREATOR_HPP

#include <set>
#include <string>
#include "Obstacle.hpp"

struct SFC
{
    float x_max;
    float y_max;
    float x_min;
    float y_min;
    // std::vector<std::pair<float,float>> node_id; 
};

bool operator<(const SFC &a,const SFC &b)
{
    if (a.x_max != b.x_max){return a.x_max < b.x_max;}
    else if(a.y_max != b.y_max){return a.y_max < b.y_max;}
    else if(a.x_min != b.x_min){return a.x_min < b.x_min;}
    else {return a.y_min < b.y_min;}
}

class SFCMapCreator
{
    public:
        SFCMapCreator(float min_spacing,
                      std::pair<float,float> x_bounds,
                      std::pair<float,float> y_bounds,
                      std::vector<Obstacle::Box> obstacle_list);
        std::set<SFC> getSFCMap();
    
    private:
        float _min_spacing;
        unsigned int _num_obstacles;
        std::pair<float,float> _x_bounds;
        std::pair<float,float> _y_bounds;
        std::vector<Obstacle::Box> _obstacle_list;
        std::set<SFC> _sfc_list;
        std::vector<unsigned int> _left_face_orderd_indices;
        std::vector<unsigned int> _right_face_orderd_indices;
        std::vector<unsigned int> _top_face_orderd_indices;
        std::vector<unsigned int> _bottom_face_orderd_indices;
        void createSFCs();
        void createBottomSFC(unsigned int &ordered_index);
        void createRightSFC(unsigned int &ordered_index);
        void createLeftSFC(unsigned int &ordered_index);
        void createTopSFC(unsigned int &ordered_index);
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