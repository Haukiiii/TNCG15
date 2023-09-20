#pragma once
#include "dependencies.hpp"

struct Camera {
    
    //cameraplane defined as a 2x2 array of vectors(x,y,z)
    glm::vec3 cameraPlane[2][2];

    // Eye/observer position
    glm::vec3 eye; 

    std::array<Pixel, res * res >* pixels;
    
    //constructor 
    Camera(glm::vec3 eye);

    //function to create the rgb image.
    void createImage(const std::string& file_path);

    //function for rendering argumentlist containing the scene as well as the bounds of the image.
    void render(Scene& scene, size_t xLowerBound, size_t xUpperBound, size_t yLowerBound, size_t yUpperBound);
};