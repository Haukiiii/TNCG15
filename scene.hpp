#pragma once
#include "dependencies.hpp"

struct Scene {

    std::vector<Polygon*> polygon; 

    void addPolygon(Polygon* pol);

    //TODO add functions for ligthning 

    void rayTarget(Ray& ray) const;
    void traceRay(std::shared_ptr<Ray>& root) const;


};
