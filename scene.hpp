#pragma once
#include "dependencies.hpp"

struct Scene {

    std::vector<Polygon*> polygons; //stores all geometry
    std::vector<Polygon*> lights;

    void addPolygon(Polygon* pol){ polygons.push_back(pol); }

    void addLightSource(Polygon* light) { polygons.push_back(light); lights.push_back(light); }

    void rayTarget(Ray& ray) const;  //sets the 'target' variable for the input ray.
    
    void traceRay(std::shared_ptr<Ray>& rootRay) const; //traverse tree structure and trace all rays to compute radiance contribution 

    glm::dvec3 localLighting(const Ray& incomingRay) const;
};
