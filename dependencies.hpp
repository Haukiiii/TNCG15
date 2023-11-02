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
constexpr float epsilon{ 1e-4f }; // Used to address precision/numerical stability issues that can arise due to limited float-precision 
constexpr float RAY_OFFSET{ 3e-2f }; // Used to avoid self-intersections when tracing reflected rays
constexpr int AMOUNT_SHADOWRAYS{ 1 }; // Multiple shadowrays can generate 'soft shadows'
constexpr int DIFF_BOUNCES{ 1 }; // Amount of sampled diffuse bounces
constexpr int MAX_DEPTH{ 12 }; // Maximum depth of a ray tree 12
constexpr float IMPORTANCE_THRESHOLD{0.1f}; // Rays with importance below threshold will be discarded
constexpr float MAX_ABS{ 0.65f }; // Can vary widely depending on the material you are simulating. For common materials, it might range from 0.1 to 10. Materials with higher absorption coefficients will appear darker and more absorbent.
constexpr float MIN_ABS{ 0.33f }; // Should be close to 0, a very small positive number for materials that you want to appear bright and reflective, such as diffuse materials with little absorption.
constexpr float FLUX_DROPOFF{ 2.0f }; // Used to simulate how light intensity decreases with distance.
constexpr float REFLECTIVE_INDEX_AIR = 1.0f;
constexpr float REFLECTIVE_INDEX_GLASS = 1.5f;
constexpr float REFLECTIVE_INDEX_GLOBAL = REFLECTIVE_INDEX_AIR; 

constexpr size_t res{ 200 }; //resolution of the image (res*res) 800
constexpr int samples{ 16 }; 

//predefined colors
constexpr glm::dvec3 red{ 1.0, 0.0, 0.0 };
constexpr glm::dvec3 green{ 0.0, 1.0, 0.0 };
constexpr glm::dvec3 blue{ 0.0, 0.0, 1.0 };
constexpr glm::dvec3 yellow{ 1.0, 1.0, 0.0 };
constexpr glm::dvec3 pink{ 1.0, 0.4, 0.7 }; 
constexpr glm::dvec3 purple{ 1.0, 0.0, 1.0 };
constexpr glm::dvec3 cyan{ 0.0, 1.0, 1.0 };
constexpr glm::dvec3 teal{ 0.0, 0.5, 0.5 };
constexpr glm::dvec3 lightgray{0.75, 0.75, 0.75 };
constexpr glm::dvec3 gray{0.5, 0.5, 0.5 };
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
