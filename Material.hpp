#pragma once
#include "dependencies.hpp"

struct Material {
    glm::dvec3 color;
    double emittance { 0.0 }; //property of a material to emit light or radiation, used for lightsources.
    double absorption { 0.0 }; //absorption will determine how much light the material absorbs when rays interact with it
    
    //constructors
    Material() : color{ black }{}
    Material(const glm::dvec3& color) : color{ color }{}
    Material(const glm::dvec3& color, double emittance) : color{ color }, emittance{ emittance }{} //constructor used when creating material for a light source.

    virtual std::shared_ptr<Ray> BRDF(const std::shared_ptr<Ray> &incoming) const = 0;
};

//---------------Subclasses of Material---------------//
struct Diffuse : public Material {

    double reflectance;

    Diffuse() : Material{ black } {};
    Diffuse(const glm::dvec3& color) : Material{ color } {}

    std::shared_ptr<Ray> BRDF(const std::shared_ptr<Ray>& incomingRay) const override;
};


struct Mirror: public Material{

    Mirror();

    std::shared_ptr<Ray> BRDF(const std::shared_ptr<Ray> &incomingRay) const override;
};

struct LightSource: public Material {

    LightSource(const glm::dvec3 color, double emittance) : Material(color, emittance){}

    std::shared_ptr<Ray> BRDF(const std::shared_ptr<Ray> &incomingRay) const override;
};
