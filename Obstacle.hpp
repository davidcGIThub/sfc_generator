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

    std::string boxToString(Box box)
    {
            return "max(x,y): (" + std::to_string(box.max_x) + "," + std::to_string(box.max_y) +
                ") , min(x,y): (" + std::to_string(box.min_x) + "," + std::to_string(box.min_y);
    }

    bool compareLeftFace(Box a, Box b)
    {
        // Returns true if the left face of Box a is 
        // further left than the left face of obstalce b
        bool is_further_left = a.min_x < b.min_x;
        return is_further_left;
    }

    bool compareRightFace(Box a, Box b)
    {
        // Returns true if the right face of Box a is 
        // further left than the right face of obstalce b
        bool is_further_left = a.max_x < b.max_x;
        return is_further_left;
    }

    bool compareTopFace(Box a, Box b)
    {
        bool is_below = a.max_y < b.max_y;
        return is_below;
    }

    bool compareBottomFace(Box a, Box b)
    {
        bool is_below = a.min_y < b.min_y;
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
            //left faces sorted in ascending order of furthest right to furthest left
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareLeftFace(unordered_obstalces[j],unordered_obstalces[i]);});
        }
        else if (face == "right")
        {
            //right faces sorted in ascending order of furthest left to furthest right
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareRightFace(unordered_obstalces[i],unordered_obstalces[j]);});
        }
        else if (face == "top")
        {
            //top faces sorted in ascending order of furthest down to furthest up
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareTopFace(unordered_obstalces[i],unordered_obstalces[j]);});
        }
        else if (face == "bottom")
        {
            //bottom faces sorted in ascending order of furthest up to furthest down
            std::sort(indices_array.begin(),indices_array.end(), 
                [&](int i,int j){return compareBottomFace(unordered_obstalces[j], unordered_obstalces[i]);});
        }
        return indices_array;
    }
}