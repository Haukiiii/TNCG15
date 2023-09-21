#pragma once  // This ensures that the header file is included only once

#include "dependencies.hpp"

struct Material {
    glm::dvec3 color;
    double emittance { 0.0 };
    double absorption { 0.0 };
    

    Material();
    Material(const glm::dvec3& color);
    Material(const glm::dvec3& color, double emittance);
};
