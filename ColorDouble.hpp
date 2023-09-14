#pragma once

#include "dependencies.hpp"

struct ColorDouble
{
    glm::dvec3 rgb;
    ColorDouble(double r, double g, double b) : rgb(r, g, b) {}
};