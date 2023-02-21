#include "Obstacle.hpp"

namespace Obstacle
{
    std::string boxToString(Box &box)
    {
            return "max(x,y): (" + std::to_string(box.max_x) + "," + std::to_string(box.max_y) +
                ") , min(x,y): (" + std::to_string(box.min_x) + "," + std::to_string(box.min_y);
    }

    bool operator<(const Face a,const Face b)
    {
        return a.position < b.position;
    }

    bool compareFace(Face &a, Face &b)
    {
        bool a_is_greater = a.position > b.position;
        return a_is_greater;
    }

    std::vector<Face> sortVerticalFaces(std::vector<Box> &unordered_obstacles)
    {
        //returns array of sorted indices of the Box array
        int num_boxs = unordered_obstacles.size();
        std::set<Face> faces_set;
        for(unsigned int i = 0; i<num_boxs; i++)
        {
            Side left_side{left};
            Side right_side{right};
            Face left_face{i,unordered_obstacles[i].min_x,left_side};
            Face right_face{i,unordered_obstacles[i].max_x,right_side};
            faces_set.insert(left_face);
            faces_set.insert(right_face);
        }
        std::vector<Face> faces_vector(faces_set.begin(), faces_set.end());
        return faces_vector;
    }

    std::vector<Face> sortHorizontalFaces(std::vector<Box> &unordered_obstacles)
    {
        //returns array of sorted indices of the Box array
        int num_boxs = unordered_obstacles.size();
        std::set<Face> faces_set;
        for(unsigned int i = 0; i<num_boxs; i++)
        {
            Side top_side{top};
            Side bottom_side{bottom};
            Face top_face{i,unordered_obstacles[i].max_y,top_side};
            Face bottom_face{i,unordered_obstacles[i].min_y,bottom_side};
            faces_set.insert(top_face);
            faces_set.insert(bottom_face);
        }
        std::vector<Face> faces_vector(faces_set.begin(), faces_set.end());
        return faces_vector;
    }

    // bool compareLeftFace(Box &a, Box &b)
    // {
    //     // Returns true if the left face of Box a is 
    //     // further left than the left face of obstalce b
    //     bool is_further_left = a.min_x < b.min_x;
    //     return is_further_left;
    // }

    // bool compareRightFace(Box &a, Box &b)
    // {
    //     // Returns true if the right face of Box a is 
    //     // further left than the right face of obstalce b
    //     bool is_further_left = a.max_x < b.max_x;
    //     return is_further_left;
    // }

    // bool compareTopFace(Box &a, Box &b)
    // {
    //     bool is_below = a.max_y < b.max_y;
    //     return is_below;
    // }

    // bool compareBottomFace(Box &a, Box &b)
    // {
    //     bool is_below = a.min_y < b.min_y;
    //     return is_below;
    // }

    // std::vector<unsigned int> sortBoxIndices(std::vector<Box> &unordered_obstacles, std::string face)
    // {
    //     //returns array of sorted indices of the Box array
    //     int num_Boxs = unordered_obstacles.size();
    //     std::vector<unsigned int> indices_array(num_Boxs);
    //     std::iota(indices_array.begin(),indices_array.end(),0); //Initializing
    //     if(face == "left")
    //     {
    //         //left faces sorted in ascending order of furthest left to furthest right
    //         std::sort(indices_array.begin(),indices_array.end(), 
    //             [&](int i,int j){return compareLeftFace(unordered_obstacles[i],unordered_obstacles[j]);});
    //     }
    //     else if (face == "right")
    //     {
    //         //right faces sorted in ascending order of furthest right to furthest left
    //         std::sort(indices_array.begin(),indices_array.end(), 
    //             [&](int i,int j){return compareRightFace(unordered_obstacles[j],unordered_obstacles[i]);});
    //     }
    //     else if (face == "top")
    //     {
    //         //top faces sorted in ascending order of furthest up to furthest down
    //         std::sort(indices_array.begin(),indices_array.end(), 
    //             [&](int i,int j){return compareTopFace(unordered_obstacles[j],unordered_obstacles[i]);});
    //     }
    //     else if (face == "bottom")
    //     {
    //         //bottom faces sorted in ascending order of furthest down to furthest up
    //         std::sort(indices_array.begin(),indices_array.end(), 
    //             [&](int i,int j){return compareBottomFace(unordered_obstacles[i], unordered_obstacles[j]);});
    //     }
    //     return indices_array;
    // }

    std::vector<Box> createRandomObstacleList(unsigned int &num_obstacles, float &max_x_bound, float &max_y_bound,
                                            float &min_x_bound, float &min_y_bound, float &max_thickness, float &min_thickness)
    {
        srand (time(NULL));
        std::vector<Box> obstacle_list;
        Box box1 = createRandomBox(max_x_bound, max_y_bound, min_x_bound, min_y_bound, max_thickness, min_thickness);
        obstacle_list.push_back(box1);
        srand (time(NULL));
        for(unsigned int i=1; i<num_obstacles; i++)
        {
            Box box = createRandomBox(max_x_bound, max_y_bound, min_x_bound, min_y_bound, max_thickness, min_thickness);
            bool overlaps{false};
            for(auto obstacle: obstacle_list)
            {
                if(check_overlap(box, obstacle))
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
        return obstacle_list;
    }

    bool check_overlap(Box &box1, Box &box2)
    {
        bool overlaps{false};
        float box1_x_center = (box1.max_x + box1.min_x)/2;
        float box1_y_center = (box1.max_y + box1.min_y)/2;
        float box2_x_center = (box2.max_x + box2.min_x)/2;
        float box2_y_center = (box2.max_y + box2.min_y)/2;
        float min_x_distance = ((box1.max_x - box1.min_x) + (box2.max_x - box2.min_x))/2;
        float min_y_distance = ((box1.max_y - box1.min_y) + (box2.max_y - box2.min_y))/2;
        if(abs(box2_x_center - box1_x_center) < min_x_distance)
        {
            if(abs(box2_y_center - box1_y_center) < min_x_distance)
            {
                overlaps = true;
            }
        }
        return overlaps;
    }

    float* createRandomObstacleArray(unsigned int num_obstacles, float max_x_bound, float max_y_bound,
                                            float min_x_bound, float min_y_bound, float max_thickness, float min_thickness)
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
        float center_x = min_x_bound + max_thickness/2 + static_cast <float> (rand()) /
                (static_cast <float> (RAND_MAX / (max_x_bound - max_thickness - min_x_bound)));
        float center_y = min_y_bound + max_thickness/2 + static_cast <float> (rand()) /
                (static_cast <float> (RAND_MAX / (max_y_bound - max_thickness - min_y_bound)));
        float x_thickness = min_thickness + static_cast <float> (rand()) / 
                            (static_cast <float> (RAND_MAX / (max_thickness-min_thickness)));
        float y_thickness = min_thickness + static_cast <float> (rand()) / 
                            (static_cast <float> (RAND_MAX / (max_thickness-min_thickness)));
        float box_x_min = center_x - x_thickness/2;
        float box_y_min = center_y - y_thickness/2;
        float box_x_max = center_x + y_thickness/2;
        float box_y_max = center_y + y_thickness/2;
        Box box{box_x_max, box_y_max, box_x_min, box_y_min};
        return box;

    }

}