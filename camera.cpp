#pragma once
#include "dependencies.hpp"
//constuctor with a vec3 eye position as argument.
Camera::Camera(glm::vec3 eye) : eye{ eye } {

    //creating the camera plane
    cameraPlane[0][0] = glm::vec3(0.0f, -1.0f, -1.0f); //Bottom left corner
    cameraPlane[0][1] = glm::vec3(0.0f, 1.0f, -1.0f); //Bottom right corner
	cameraPlane[1][0] = glm::vec3(0.0f, -1.0f, 1.0f); //Top left corner
	cameraPlane[1][1] = glm::vec3(0.0f, 1.0f, 1.0f); //Top right corner

    pixels = new std::array<Pixel, res*res>(); 
    pixels->fill(Pixel{ glm::dvec3(0.0, 0.0, 0.0) }); //may not be needed (ensure pixels initialized with black)
}
    void Camera::render(Scene& scene, size_t xLowerBound, size_t xUpperBound, size_t yLowerBound, size_t yUpperBound) {

    }

