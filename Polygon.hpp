#pragma once
#include "dependencies.hpp"

struct Polygon
{

    const Material* material; 

    Polygon(const Material* material): material{ material } {};

    Polygon() = default; //default constuctor, creates a black material with 0 absoption and 0 emittance

    virtual glm::vec3 CalcUnitNormal(const glm::vec3& hit) = 0; //method to compute unit normal, will be overrided in subclasses

    virtual float rayIntersection(Ray* ray) = 0; //method to calculate ray intersection with rect/triangle, overrides in both subclasses.

    virtual std::shared_ptr<Ray> generateShadowRays(const glm::vec3& start) = 0;
};


struct Triangle: public Polygon 
{
    std::array<glm::vec3, 3> vertices;
    glm::vec3 normal;
    glm::vec3 edge1;
    glm::vec3 edge2;

    Triangle() = default;
    Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const Material* material);

    glm::vec3 CalcUnitNormal(const glm::vec3& hit) override;

    float rayIntersection(Ray* ray) override; //method for calulating ray intersection with triangle, returns the parameter t which determines a point on a ray

    std::shared_ptr<Ray> generateShadowRays(const glm::vec3& start) override;
};

struct Rectangle: public Polygon
{
    std::array<glm::vec3, 4> vertices;
	glm::vec3 normal;
	glm::vec3 edge1;
	glm::vec3 edge2;
	glm::vec3 edge3;
    
	Rectangle() = default;
    Rectangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const Material* material);
    
    glm::vec3 CalcUnitNormal(const glm::vec3& hit) override;

    std::shared_ptr<Ray> generateShadowRays(const glm::vec3& start) override; // kanske onädig då vi bara använder triagnlar?

    float rayIntersection(Ray* ray) override; //method for calulating ray intersection with rectangle, returns the parameter t which determines a point on a ray
};
