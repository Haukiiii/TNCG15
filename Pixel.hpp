#pragma once
#include "dependencies.hpp"

//Struct pixel stores a double colorvalue for red green and blue.
struct Pixel {

glm::dvec3 pixelColor;

//constructor initializing pixelcolor to black
Pixel() : pixelColor{glm::dvec3(0.0, 0.0, 0.0)} {}

//contructor initializing a pixel with a specified dvec3 color
Pixel(glm::dvec3 color) : pixelColor {color} {}

};