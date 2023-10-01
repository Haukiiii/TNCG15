#pragma once
#include "dependencies.hpp"

struct Ray {

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

};
