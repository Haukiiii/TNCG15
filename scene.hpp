#pragma once
#include "dependencies.hpp"

struct Scene {

    std::vector<Polygon*> polygon; //stores all geometry

    void addPolygon(Polygon* pol);

    //TODO add functions for ligthning 

    //iterates through all objects in the scene, checks for intersections between the ray and each object. keeps track of the closest intersection point found
    void rayTarget(Ray& ray) const; 
    
    void traceRay(std::shared_ptr<Ray>& root) const;
};