#pragma once
#include "dependencies.hpp"

struct Material {
    glm::dvec3 color;
    double emittance{ 0.0 }; //property of a material to emit light or radiation, used for lightsources.
    double absorption{ 0.0 }; // determines how much light the material absorbs when rays interact with it based on color of material
    
    //constructors
    Material() : color{ black }{}
    Material(const glm::dvec3& color) : color{ color }{}
    Material(const glm::dvec3& color, double emittance) : color{ color }, emittance{ emittance }{} //constructor used when creating material for a light source.

    virtual std::vector<Ray> BRDF(const std::shared_ptr<Ray> &incoming) const = 0;
};

//---------------Subclasses of Material---------------//

//Mirror material, perfect reflection
struct Mirror: public Material{

    Mirror() : Material(){}

    std::vector<Ray> BRDF(const std::shared_ptr<Ray> &incomingRay) const override;
};

//Diffuse Lambertian material
struct Diffuse : public Material {

    double reflectance; 

    Diffuse(const glm::dvec3& color, double reflectance) : Material{ color }, reflectance{ reflectance } {this->absorption = MAX_ABS - (MAX_ABS - MIN_ABS) * glm::length(color) / glm::length(white);}

    std::vector<Ray> BRDF(const std::shared_ptr<Ray>& incomingRay) const override;
};

struct LightSource: public Material {

    LightSource(const glm::dvec3& color, double emittance) : Material(color, emittance){}

    std::vector<Ray> BRDF(const std::shared_ptr<Ray> &incomingRay) const override; //Rays stop at lightsources
};
