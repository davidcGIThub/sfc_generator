#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <vector>
#include <set>
#include <string>
#include <numeric> 
#include <algorithm>
#include <iostream>

namespace Obstacle
{
    struct Box
    {
        float max_x;
        float max_y;
        float min_x;
        float min_y;
    };

    enum Side{top,bottom,left,right};

    struct Face
    {
        unsigned int obstacle_index;
        float position; 
        Side side;
    };
    bool operator<(const Face a,const Face b);
    std::vector<Face> sortVerticalFaces(std::vector<Box> &unordered_obstacles);
    std::vector<Face> sortHorizontalFaces(std::vector<Box> &unordered_obstacles);
    std::string boxToString(Box &box);
    // bool compareLeftFace(Box &a, Box &b);
    // bool compareRightFace(Box &a, Box &b);
    // bool compareTopFace(Box &a, Box &b);
    // bool compareBottomFace(Box &a, Box &b);
    // std::vector<unsigned int> sortBoxIndices(std::vector<Box> &unordered_obstacles, std::string face);
    std::vector<Box> createRandomObstacleList(unsigned int &num_obstacles, float &max_x_bound, 
                                            float &max_y_bound, float &min_x_bound, float &min_y_bound, 
                                            float &max_thickness, float &min_thickness);
    Box createRandomBox(float &max_x_bound, float &max_y_bound, float &min_x_bound, 
                        float &min_y_bound, float &max_thickness, float &min_thickness);
    bool check_overlap(Box &box1, Box &box2);
    extern "C"
    float* createRandomObstacleArray(unsigned int num_obstacles, float max_x_bound, float max_y_bound,
                                    float min_x_bound, float min_y_bound, float max_thickness, float min_thickness);
}

#endif