#include "dependencies.hpp"

Triangle::Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const Material* material) : Polygon{ material } {
    //set verticies
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
    //get edges
	edge1 = v2 - v1;
	edge2 = v3 - v1;
    //get unit normal
    normal = glm::normalize(glm::cross(edge2, edge1));
}

Rectangle::Rectangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const Material* material) : Polygon { material }{
   
    //set verticies
    vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
    vertices[3] = v4;
    //get edges
    edge1 = v2 - v1;
	edge2 = v3 - v1;
	edge3 = v4 - v1;
    //get unit normal
    normal = glm::normalize(glm::cross(edge2, edge1));
}

//functions to get the normals of each shape
glm::vec3 Triangle::CalcUnitNormal(const glm::vec3& hit)
{
	return glm::normalize(glm::cross(this->edge1, this->edge2));
}

glm::vec3 Rectangle::CalcUnitNormal(const glm::vec3& hit)
{
	return glm::normalize(glm::cross(this->edge1, this->edge2));
}
