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
        SFCMapCreator(float min_spacing, float x_max,
                      float y_max, float x_min, float y_min,
                      unsigned int num_obstacles, float obstacle_array[]);
        SFCMapCreator(float min_spacing, float x_max,
                      float y_max, float x_min, float y_min,
                      unsigned int num_obstacles, std::vector<Obstacle::Box> obstacle_list);
        unsigned int getNumberOfSFCs();
        float* getSFCArray();
        void printSFCs();
    
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
        std::vector<Obstacle::Box> convertObstacleArrayToVector(float obstacle_array[]);
};

extern "C"
{
    SFCMapCreator* SFCMapCreator_new(float min_spacing, float x_max,
                      float y_max, float x_min, float y_min,
                      unsigned int num_obstacles, float obstacle_array[]) 
                    {return new SFCMapCreator(min_spacing, x_max,
                      y_max, x_min, y_min, num_obstacles, obstacle_array);}
    unsigned int getNumberOfSFCs_new(SFCMapCreator* creator) {creator->getNumberOfSFCs();}
    float* getSFCs_new(SFCMapCreator* creator) {creator->getSFCs();}
    void printSFCs_new(SFCMapCreator* creator) {creator->printSFCs();}
}
#endif