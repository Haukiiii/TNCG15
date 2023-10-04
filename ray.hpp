#pragma once
#include "dependencies.hpp"

struct Ray : public std::enable_shared_from_this<Ray>{ //to use share_from_this() in countRays().

glm::vec3 startpoint;
glm::vec3 endpoint;
glm::vec3 direction;

double importance;
double radiance;

Polygon* target; //used to store information about the object or surface that the ray intersects.
std::shared_ptr<Ray> prev; //ptr to previous ray
std::shared_ptr<Ray> next; //ptr to next ray

int depth{ 0 }; // check the depth of tree
bool is_leaf{ false }; // if the ray is the last

//constructors
Ray() = default;
Ray(glm::vec3 startpoint, glm::vec3 endpoint);
Ray(glm::vec3 startpoint, glm::vec3 endpoint, double importance);

//
void setEndpoint(float t);

int countRays(); //returns number of rays in list of current ray. 
//Alternativt lägg till en count variabel i ray som håller koll på antalet rays i listan...?
};
