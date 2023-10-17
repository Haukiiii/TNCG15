#pragma once
#include "dependencies.hpp"

struct Polygon
{

    const Material* material; 

    Polygon(const Material* material): material{ material } {};

    Polygon() = default; //default constuctor, creates a black material with 0 absoption and 0 emittance

    virtual glm::vec3 CalcUnitNormal(const glm::vec3& hit) const = 0; //method to compute unit normal, will be overrided in subclasses

    virtual float rayIntersection(Ray* ray) const = 0; //method to calculate ray intersection with rect/triangle, overrides in both subclasses.

    virtual std::vector<Ray> generateShadowRays(const glm::vec3& startpoint) const = 0;
};


struct Triangle: public Polygon 
{
    std::array<glm::vec3, 3> vertices;
    glm::vec3 normal;
    glm::vec3 edge1;
    glm::vec3 edge2;

    Triangle() = default;
    Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const Material* material);

    glm::vec3 CalcUnitNormal(const glm::vec3& hit) const override { return glm::normalize(glm::cross(this->edge1, this->edge2)); }

    float rayIntersection(Ray* ray) const override; //method for calulating ray intersection with triangle, returns the parameter t which determines a point on a ray

    std::vector<Ray> generateShadowRays(const glm::vec3& startpoint) const override; //generates shadowrays with random endpoint on triangular lightsource
};

struct Sphere : public Polygon {

    glm::vec3 position;
    float radius;

    Sphere(const glm::vec3& pos, float rad, const Material* material)
        : Polygon{ material }, position{ pos }, radius{ rad } {};

    float rayIntersection(Ray* ray) const override;
    std::vector<Ray> generateShadowRays(const glm::vec3& startpoint) const override;
    glm::vec3 CalcUnitNormal(const glm::vec3& hit) const override { return glm::normalize(hit - this->position); }
};

struct Box : public Triangle {

    std::array<glm::vec3, 8> corners;
    std::array<Triangle, 12> triangles;

    Box() = default;
    Box(const glm::vec3& pos, float height, float depth, float width, const Material* material);
};

