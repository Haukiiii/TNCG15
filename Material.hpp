#pragma once
#include "dependencies.hpp"

struct Material {
    glm::dvec3 color;
    double emittance { 0.0 }; //property of a material to emit light or radiation, used for lightsources.
    double absorption { 0.0 }; //absorption will determine how much light the material absorbs when rays interact with it
    
    //constructors
    Material();
    Material(const glm::dvec3& color);
    Material(const glm::dvec3& color, double emittance); //constructor used when creating material for a light source.

};
