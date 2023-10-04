#include "dependencies.hpp"

//constructor using start/endpoint, importance initialized with 1.0
Ray::Ray(glm::vec3 startpoint, glm::vec3 endpoint) 
: startpoint{ startpoint }, endpoint{ endpoint }, direction{glm::normalize( endpoint- startpoint)},
 importance{ 1.0 }, radiance{ black }, 
 target{ nullptr }, parent{ nullptr } {}

//constructor using start/endpoint and importance.
 Ray::Ray(glm::vec3 startpoint, glm::vec3 direction, double importance) 
: startpoint{ startpoint }, endpoint{ glm::vec3(0.0f, 0.0f, 0.0f)}, direction{glm::normalize(direction)},
 importance{ importance }, radiance{ black }, 
 target{ nullptr }, parent{ nullptr } {} //kanske inte behöver göra parent t nullptr här***

 void Ray::setEndpoint(float t) { //ray parameterized using t

    endpoint = (startpoint + (direction * t));
 }
