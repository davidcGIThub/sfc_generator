#include <vector>
#include <string>
#include <numeric> 
#include <algorithm>
#include <iostream>

namespace Obstacle
{
    struct Box
    {
        float x_center;
        float y_center;
        float width;
        float height;
    };

    std::string boxToString(Box box)
    {
            return "(x,y): (" + std::to_string(box.x_center) + "," + std::to_string(box.y_center) +
                ") , width: " + std::to_string(box.width) + " , height: " + std::to_string(box.height);
    }

    bool compareLeftFace(Box a, Box b)
    {
        // Returns true if the left face of Box a is 
        // further left than the left face of obstalce b
        float a_left_face = a.x_center - a.width/2.0;
        float b_left_face = b.x_center - b.width/2.0;
        bool is_further_left = a_left_face < b_left_face;
        return is_further_left;
    }

    bool compareRightFace(Box a, Box b)
    {
        // Returns true if the right face of Box a is 
        // further left than the right face of obstalce b
        float a_right_face = a.x_center + a.width/2.0;
        float b_right_face = b.x_center + b.width/2.0;
        bool is_further_left = a_right_face < b_right_face;
        return is_further_left;
    }

    bool compareTopFace(Box a, Box b)
    {
        float a_top_face = a.y_center + a.height/2.0;
        float b_top_face = b.y_center + b.height/2.0;
        bool is_below = a_top_face < b_top_face;
        return is_below;
    }

    bool compareBottomFace(Box a, Box b)
    {
        float a_bottom_face = a.y_center - a.height/2.0;
        float b_bottom_face = b.y_center - b.height/2.0;
        bool is_below = a_bottom_face < b_bottom_face;
        return is_below;
    }

    std::vector<unsigned int> sortBoxIndices(std::vector<Box> unordered_obstalces, std::string face)
    {
        //returns array of sorted indices of the Box array
        int num_Boxs = unordered_obstalces.size();
        std::vector<unsigned int> indices_array(num_Boxs);
        std::iota(indices_array.begin(),indices_array.end(),0); //Initializing
        if(face == "left")
        {
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareLeftFace(unordered_obstalces[i],unordered_obstalces[j]);} );
        }
        else if (face == "right")
        {
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareRightFace(unordered_obstalces[i],unordered_obstalces[j]);} );
        }
        else if (face == "top")
        {
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareTopFace(unordered_obstalces[i],unordered_obstalces[j]);} );
        }
        else if (face == "bottom")
        {
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareBottomFace(unordered_obstalces[i],unordered_obstalces[j]);} );
        }
        return indices_array;
    }
}