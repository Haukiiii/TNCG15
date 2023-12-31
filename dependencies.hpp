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
constexpr float RAY_OFFSET = 1e-3f; //used to avoid self-intersections when tracing reflected rays
constexpr int DIFF_BOUNCES = 1;
constexpr int MAX_RAYS_IN_LIST = 12; 
constexpr float treshold_importance = 0.1f;

constexpr double g_color_contribution = 0.3; // vet inte riktigt vad denna är till för 


constexpr size_t res = 800; //resolution of the image (res*res)
constexpr int samples = 4;

//predefined colors
constexpr glm::dvec3 red{ 1.0, 0.0, 0.0 };
constexpr glm::dvec3 green{ 0.0, 1.0, 0.0 };
constexpr glm::dvec3 blue{ 0.0, 0.0, 1.0 };
constexpr glm::dvec3 yellow{ 1.0, 1.0, 0.0 };
constexpr glm::dvec3 pink{ 1.0, 0.4, 0.7 }; 
constexpr glm::dvec3 purple{ 1.0, 0.0, 1.0 };
constexpr glm::dvec3 cyan{ 0.0, 1.0, 1.0 };
constexpr glm::dvec3 teal{ 0.0, 0.5, 0.5 };
constexpr glm::dvec3 gary{0.5, 0.5, 0.5 };
constexpr glm::dvec3 black{ 0.0, 0.0 ,0.0 };
constexpr glm::dvec3 white{ 1.0, 1.0, 1.0 }; 



//structs/headers
struct Room;
struct Pixel;
struct Polygon;
struct Scene;
struct Ray;
struct Camera;
struct Material;


#include "Pixel.hpp"
#include "Polygon.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
#include "Room.hpp"
#include "Material.hpp"

#endif
