#include <vector>
#include <string>
#include <numeric> 
#include <algorithm>
#include <iostream>

struct Obstacle
{
    float x_center;
    float y_center;
    float width;
    float height;
    std::string toString()
    {
        return "(x,y): (" + std::to_string(x_center) + "," + std::to_string(y_center) +
             ") , width: " + std::to_string(width) + " , height: " + std::to_string(height);
    }
};

bool compareLeftFace(Obstacle a, Obstacle b)
{
    // Returns true if the left face of obstacle a is 
    // further left than the left face of obstalce b
    float a_left_face = a.x_center - a.width/2.0;
    float b_left_face = b.x_center - b.width/2.0;
    bool is_further_left = a_left_face < b_left_face;
    return is_further_left;
}

bool compareRightFace(Obstacle a, Obstacle b)
{
    // Returns true if the right face of obstacle a is 
    // further left than the right face of obstalce b
    float a_right_face = a.x_center + a.width/2.0;
    float b_right_face = b.x_center + b.width/2.0;
    bool is_further_left = a_right_face < b_right_face;
    return is_further_left;
}

bool compareTopFace(Obstacle a, Obstacle b)
{
    float a_top_face = a.y_center + a.height/2.0;
    float b_top_face = b.y_center + b.height/2.0;
    bool is_below = a_top_face < b_top_face;
    return is_below;
}

bool comparebottomFace(Obstacle a, Obstacle b)
{
    float a_bottom_face = a.y_center - a.height/2.0;
    float b_bottom_face = b.y_center - b.height/2.0;
    bool is_below = a_bottom_face < b_bottom_face;
    return is_below;
}

std::vector<unsigned int> sortIndices(std::vector<Obstacle> unordered_obstalces, std::string face)
{
    //returns array of sorted indices of the obstacle array
    int num_obstacles = unordered_obstalces.size();
    std::vector<unsigned int> indices_array(num_obstacles);
    std::iota(indices_array.begin(),indices_array.end(),0); //Initializing
    if(face == "left")
    std::sort(indices_array.begin(),indices_array.end(), 
        [&](int i,int j){return compareLeftFace(unordered_obstalces[i],unordered_obstalces[j]);} );
    return indices_array;
}

int main()
{
    Obstacle obstacle1{11,7,1,1};
    Obstacle obstacle2{3.1,7,2,1};
    Obstacle obstacle3{7,2,2,1};
    Obstacle obstacle4{2,3,1,2};
    std::vector<Obstacle> vec = {obstacle1, obstacle2, obstacle3, obstacle4};
    std::vector<unsigned int> sortedIndices = sortIndices(vec, "left");
    for(auto i: sortedIndices)
    {
        std::cout << i;
    }
    return 0;
}