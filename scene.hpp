#pragma once
#include "dependencies.hpp"

struct Scene {

    std::vector<Polygon*> polygons; //stores all geometry
    std::vector<Polygon*> ligths;

    void addPolygon(Polygon* pol);

    void rayTarget(Ray& ray) const;  //sets the 'target' variable for the input ray.
    
    void traceRay(std::shared_ptr<Ray>& rootRay) const; //traverse tree structure and trace all rays to compute radiance contribution 

    glm::dvec3 localLighting(const Ray& incomingRay) const;
};
