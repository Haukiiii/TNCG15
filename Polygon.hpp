#include "dependencies.hpp"

struct Polygon
{
    ColorDouble color; //ändra eventuellt till material senare?
    glm::vec3 unitNormal;


    Polygon() = default; //default constuctor

    virtual glm::vec3 CalcUnitNormal(const glm::vec3& hit); //method to compute unit normal
};


struct Triangle: public Polygon 
{
    glm::vec3 CalcUnitNormal(const glm::vec3& hit) override;
};

struct Rectangle: public Polygon
{
    glm::vec3 CalcUnitNormal(const glm::vec3& hit) override;
};
