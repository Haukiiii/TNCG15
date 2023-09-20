#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef TYPEDEFS_DEPENDENCIES
#define TYPEDEFS_DEPENDENCIES

#include <cstddef> //to use size_t? Should work just by compiling with c++20
//settings
constexpr size_t res = 800; //resolution of the image (res*res)

//predefined colors
/* const glm::dvec3 red{ 1.0, 0.0, 0.0 };
const glm::dvec3 green{ 0.0, 1.0, 0.0 };
const glm::dvec3 blue{ 0.0, 0.0, 1.0 };
const glm::dvec3 yellow{ 1.0, 1.0, 0.0 };
const glm::dvec3 pink{ 1.0, 0.4, 0.7 }; 
const glm::dvec3 purple{ 1.0, 0.0, 1.0 };
const glm::dvec3 cyan{ 0.0, 1.0, 1.0 };
const glm::dvec3 teal{ 0.0, 0.5, 0.5 };
const glm::dvec3 black{ 0.0, 0.0 ,0.0 };
const glm::dvec3 white{ 1.0, 1.0, 1.0 }; */

//libraries
#include <iostream>
#include <array>
#include <vector>
#include "./glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include <cstdlib>

//structs/headers
struct Pixel;
struct Object;
struct Scene;
struct Ray;
struct Camera;

#include "Pixel.hpp"
#include "Polygon.hpp"
#include "Room.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

#endif