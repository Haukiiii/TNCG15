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

    //function returning reference to a pixel at row 'i' column 'j'
    Pixel& getPixel(size_t i, size_t j);
    
    //function to create the rgb image.
    void createImage(const std::string& file_path);

    //main rendering function, sends a ray from the eye position through each pixel, argumentlist: the scene as well as the bounds of the image.
    void render(Scene& scene, size_t xLowerBound, size_t xUpperBound, size_t yLowerBound, size_t yUpperBound);
};