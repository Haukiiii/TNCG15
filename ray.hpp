#pragma once
#include "dependencies.hpp"

struct Ray { 

glm::vec3 startpoint;
glm::vec3 endpoint;
glm::vec3 direction;
glm::dvec3 radiance;
double importance;

bool inside_transparent_object{ false };
Polygon* target; //used to store information about the object or surface that the ray intersects.

//---variables for tree datastructure---//
bool is_leaf{ false }; // if the ray is the last

int depth{ 0 }; // check the depth of tree
std::shared_ptr<Ray> parent; //ptr to parent ray.
std::vector<std::shared_ptr<Ray>> children; //vector with all child-nodes of the ray.

//constructors
Ray() = default;
Ray(glm::vec3 startpoint, glm::vec3 endpoint);
Ray(glm::vec3 startpoint, glm::vec3 direction, double importance);

void setEndpoint(float t); //sets endpoint of the ray using parameter t

};
