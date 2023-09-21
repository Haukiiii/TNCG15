#include "dependencies.hpp"

struct Ray {

glm::vec3 origin;
glm::vec3 endpoint;
glm::vec3 direction;

double importance;
double radiance;

Polygon* target; //used to store information about the object or surface that the ray intersects.
std::shared_ptr<Ray> prev; 
std::shared_ptr<Ray> next;

//TODO constrructors


};