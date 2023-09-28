#include "dependencies.hpp"

//constructor using start/endpoint, importance initialized with 1.0
Ray::Ray(glm::vec3 startpoint, glm::vec3 endpoint) 
: startpoint{ startpoint }, endpoint{ endpoint }, direction{glm::normalize( endpoint- startpoint)},
 importance{ 1.0 }, radiance{ 0.0 }, 
 target{ nullptr }, prev{ nullptr }, next{ nullptr } {}

//constructor using start/endpoint and importance.
 Ray::Ray(glm::vec3 startpoint, glm::vec3 direction, double importance) 
: startpoint{ startpoint }, endpoint{ glm::vec3(0.0f, 0.0f, 0.0f)}, direction{glm::normalize(direction)},
 importance{ importance }, radiance{ 0.0 }, 
 target{ nullptr }, prev{ nullptr }, next{ nullptr } {} //osöker på om next och prev bör initialiserad som nullptr här*********

 void Ray::setEndpoint(const float t) { //ray parameterized using t

    endpoint = (startpoint + (direction * t));
 }