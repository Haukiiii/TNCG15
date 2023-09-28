#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef TYPEDEFS_DEPENDENCIES
#define TYPEDEFS_DEPENDENCIES
#endif

#ifndef DEPENDENCIES_HPP
#define DEPENDENCIES_HPP

//#include <cstddef> //to use size_t? Should work just by compiling with c++20


//libraries
#include <iostream>
#include <array>
#include <vector>
#include "./glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include <cstdlib>
#include <memory>
#include <fstream>
#include <chrono>
#include <thread>

//settings
constexpr float treshold_importance = 0.1f;

constexpr size_t res = 800; //resolution of the image (res*res)
constexpr int samples = 4;

//predefined colors
const glm::dvec3 red{ 1.0, 0.0, 0.0 };
const glm::dvec3 green{ 0.0, 1.0, 0.0 };
const glm::dvec3 blue{ 0.0, 0.0, 1.0 };
const glm::dvec3 yellow{ 1.0, 1.0, 0.0 };
const glm::dvec3 pink{ 1.0, 0.4, 0.7 }; 
const glm::dvec3 purple{ 1.0, 0.0, 1.0 };
const glm::dvec3 cyan{ 0.0, 1.0, 1.0 };
const glm::dvec3 teal{ 0.0, 0.5, 0.5 };
const glm::dvec3 black{ 0.0, 0.0 ,0.0 };
const glm::dvec3 white{ 1.0, 1.0, 1.0 }; 



//structs/headers
struct Room;
struct Pixel;
struct Object;
struct Scene;
struct Ray;
struct Camera;
struct Material;


#include "Pixel.hpp"
#include "Material.hpp"
#include "Polygon.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Room.hpp"

#endif
