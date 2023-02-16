#include <vector>
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

    std::string boxToString(Box &box)
    {
            return "max(x,y): (" + std::to_string(box.max_x) + "," + std::to_string(box.max_y) +
                ") , min(x,y): (" + std::to_string(box.min_x) + "," + std::to_string(box.min_y);
    }

    bool compareLeftFace(Box &a, Box &b)
    {
        // Returns true if the left face of Box a is 
        // further left than the left face of obstalce b
        bool is_further_left = a.min_x < b.min_x;
        return is_further_left;
    }

    bool compareRightFace(Box &a, Box &b)
    {
        // Returns true if the right face of Box a is 
        // further left than the right face of obstalce b
        bool is_further_left = a.max_x < b.max_x;
        return is_further_left;
    }

    bool compareTopFace(Box &a, Box &b)
    {
        bool is_below = a.max_y < b.max_y;
        return is_below;
    }

    bool compareBottomFace(Box &a, Box &b)
    {
        bool is_below = a.min_y < b.min_y;
        return is_below;
    }

    std::vector<unsigned int> sortBoxIndices(std::vector<Box> &unordered_obstacles, std::string face)
    {
        //returns array of sorted indices of the Box array
        int num_Boxs = unordered_obstacles.size();
        std::vector<unsigned int> indices_array(num_Boxs);
        std::iota(indices_array.begin(),indices_array.end(),0); //Initializing
        if(face == "left")
        {
            //left faces sorted in ascending order of furthest right to furthest left
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareLeftFace(unordered_obstacles[j],unordered_obstacles[i]);});
        }
        else if (face == "right")
        {
            //right faces sorted in ascending order of furthest left to furthest right
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareRightFace(unordered_obstacles[i],unordered_obstacles[j]);});
        }
        else if (face == "top")
        {
            //top faces sorted in ascending order of furthest down to furthest up
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareTopFace(unordered_obstacles[i],unordered_obstacles[j]);});
        }
        else if (face == "bottom")
        {
            //bottom faces sorted in ascending order of furthest up to furthest down
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareBottomFace(unordered_obstacles[j], unordered_obstacles[i]);});
        }
        return indices_array;
    }

    std::vector<Box> createRandomObstacleList(unsigned int &num_obstacles, float &max_x_bound, float &max_y_bound,
                                            float &min_x_bound, float &min_y_bound, float &max_thickness, float &min_thickness)
    {
        std::vector<Box> obstacle_list;
        Box box1 = createRandomBox(max_x_bound, max_y_bound, min_x_bound, min_y_bound, max_thickness, min_thickness);
        obstacle_list.push_back(box1);
        for(unsigned int i=1; i<num_obstacles; i++)
        {
            Box box = createRandomBox(max_x_bound, max_y_bound, min_x_bound, min_y_bound, max_thickness, min_thickness);
            bool overlaps{false};
            for(auto obstacle: obstacle_list)
            {
                if(box.max_x < obstacle.max_x && box.max_x > obstacle.min_x  
                    || box.min_x < obstacle.max_x && box.min_x > obstacle.min_x)
                {
                    overlaps = true;
                    break;
                }
            }
            if(overlaps)
            {
                i--;
            }
            else
            {
                obstacle_list.push_back(box);
            }
        }   
    }

    float* createRandomObstacleArray(unsigned int &num_obstacles, float &max_x_bound, float &max_y_bound,
                                            float &min_x_bound, float &min_y_bound, float &max_thickness, float &min_thickness)
    {
        std::vector<Box> obstacle_list = createRandomObstacleList(num_obstacles, max_x_bound, max_y_bound, min_x_bound, 
                                                                  min_y_bound, max_thickness, min_thickness);

        unsigned int count{0};
        float* obstacle_array = new float[num_obstacles*4];
        for(auto obstacle: obstacle_list)
        {
            obstacle_array[count] = obstacle.max_x;
            obstacle_array[count + num_obstacles] = obstacle.max_y;
            obstacle_array[count + 2*num_obstacles] = obstacle.min_x;
            obstacle_array[count + 3*num_obstacles] = obstacle.min_y;
            count++;
        }
        return obstacle_array;
    }

    Box createRandomBox(float &max_x_bound, float &max_y_bound, float &min_x_bound, 
                        float &min_y_bound, float &max_thickness, float &min_thickness)
    {
        srand (time(NULL));
        float center_x = min_x_bound + max_thickness/2 + static_cast <float> (rand()) /
                (static_cast <float> (RAND_MAX / (max_x_bound - max_thickness - min_x_bound)));
        float center_y = min_y_bound + max_thickness/2 + static_cast <float> (rand()) /
                (static_cast <float> (RAND_MAX / (max_y_bound - max_thickness - min_y_bound)));
        float x_thickness = min_thickness + static_cast <float> (rand()) / 
                            (static_cast <float> (RAND_MAX / (max_thickness-min_thickness)));
        float y_thickness = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/max_thickness));
        float box_x_min = center_x - x_thickness/2;
        float box_y_min = center_y - y_thickness/2;
        float box_x_max = center_x + y_thickness/2;
        float box_y_max = center_y + y_thickness/2;
        Box box{box_x_max, box_y_max, box_x_min, box_y_min};
        return box;
    }


}