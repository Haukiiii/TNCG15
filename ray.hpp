#pragma once
#include "dependencies.hpp"

struct Ray : public std::enable_shared_from_this<Ray>{ //to use share_from_this() in countRays().

glm::vec3 startpoint;
glm::vec3 endpoint;
glm::vec3 direction;
glm::dvec3 radiance;
double importance;


Polygon* target; //used to store information about the object or surface that the ray intersects.

//---variables for tree datastructure---//
bool is_leaf{ false }; // if the ray is the last
int depth{ 0 }; // check the depth of tree
std::shared_ptr<Ray> parent; //ptr to parent ray.
std::vector<std::shared_ptr<Ray>> children; //vector with all child-nodes of the ray.

//constructors
Ray() = default;
Ray(glm::vec3 startpoint, glm::vec3 endpoint);
Ray(glm::vec3 startpoint, glm::vec3 endpoint, double importance);

void setEndpoint(float t); //sets endpoint of the ray using parameter t

};
