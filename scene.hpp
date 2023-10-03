#pragma once
#include "dependencies.hpp"

struct Scene {

    std::vector<Polygon*> polygons; //stores all geometry
    std::vector<Polygon*> ligths;

    void addPolygon(Polygon* pol);

    //TODO add functions for ligthning 

    //iterates through all objects in the scene, checks for intersections between the ray and each object. keeps track of the closest intersection point found
    void rayTarget(Ray& ray) const; 
    
    void traceRay(std::shared_ptr<Ray>& root) const;

    // test
    glm::dvec3 localLighting(Ray& ray) const;
};
