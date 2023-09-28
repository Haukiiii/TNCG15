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

Pixel& Camera::getPixel(size_t i, size_t j) {
    return(*pixels)[i * res + j]; //expression computes the linear index of the pixel within the one-dimensional array represented by (*pixels)
}

void Camera::render(Scene& scene, size_t xLowerBound, size_t xUpperBound, size_t yLowerBound, size_t yUpperBound) {

    //initial setup 
    glm::vec3 start = this->eye; //set starting point of rays to the eye position of the camera.
    int pixel_dim = sqrt(samples); //used to determine the number of samples along each axis within a pixel.
    float pixel_size = glm::distance(this->cameraPlane[0][0], this->cameraPlane[0][1]) / res; // get pixel size via distance between two corners of the image plane and dividing it by resolution
    float pixel_sample_size = (pixel_size / pixel_dim); //size of each sub-sample within a pixel

    //Loops over all pixels in the camera plane and fetch them.
    for(size_t j = yLowerBound; j < yUpperBound; ++j) {
        for(size_t i = xLowerBound; i < xUpperBound; ++i) {
            Pixel& p = getPixel(i, j);

            for(size_t k = 0; k < samples; ++k) { // generate multiple samples within each pixel

                // Calculate coordinates of the sub-sample within the pixel (cordinates on the camera plane)
                float xPixelOffset = static_cast<float>(i)* pixel_size - (1.0f - pixel_size) + static_cast<float>(k % pixel_dim)* pixel_sample_size;
				float yPixelOffset = static_cast<float>(j)* pixel_size - (1.0f - pixel_size) + static_cast<float>(floor((k / pixel_dim)))* pixel_sample_size;

                // Add a random horizontal offset within the sub-sample
				xPixelOffset += static_cast<float>(rand() / RAND_MAX)* pixel_sample_size;
                // Add a random vertical offset within the sub-sample
				yPixelOffset += static_cast<float>(rand() / RAND_MAX)* pixel_sample_size;

                glm::vec3 interSectionPixel(0.0f, xPixelOffset, yPixelOffset); //The point in the cameraplane where the ray "ends"
                Ray ray{start, interSectionPixel}; 

                scene.rayTarget(ray); //this gives sets endpoint of the ray, which intersects the closest object, surface intersection information stored in ray->target

                p.pixelColor = ray.target->material->color;
            }
        }
    }
    createImage;
}

void Camera::createImage() {
    std::ofstream imageFile("output.ppm"); // Change the file name and extension as needed

    if (!imageFile.is_open()) {
        std::cerr << "Failed to open image file for writing." << std::endl;
        return;
    }

    // Write the PPM header information (P3 format for color images).
    imageFile << "P3\n" << res << " " << res << "\n255\n";

    // Iterate over each pixel and write its color to the image file.
    for (int j = 0; j < res; ++j) {
        for (int i = 0; i < res; ++i) {
            Pixel& p = getPixel(i, j);
            int r = static_cast<int>(255.999 * p.pixelColor.r);
            int g = static_cast<int>(255.999 * p.pixelColor.g);
            int b = static_cast<int>(255.999 * p.pixelColor.b);
            imageFile << r << " " << g << " " << b << "\n";
        }
    }

    imageFile.close();
    std::cout << "Image saved to output.ppm." << std::endl;
}

