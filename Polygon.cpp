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

Rectangle::Rectangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const Material* material) : Polygon { material } {
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

//Ray intersections implementations (möller trumbore)
float Triangle::rayIntersection(Ray* ray){ //lecture 4 möller trumbore 

    //check if intersection is possible (scalar product between raydirection and surface normal must be negative)
    if(glm::dot(ray->direction, normal) > 0) 
    {
        return -1.0; //no intersection possible
    }

    //define T, P, Q, already have D, E1, E2
    glm::vec3 T = ray->startpoint - vertices[0];
    glm::vec3 P = glm::cross(ray->direction, edge2);
    glm::vec3 Q = glm::cross(T, edge1); 

    //calculate barycentric coordinates of the intersection point
    glm::vec3 intersection = (1 / glm::dot(P, edge1)) * glm::vec3(glm::dot(Q, edge2), glm::dot(P, T), glm::dot(Q, ray->direction)); 

    //check if the intersection point lies within the triangle
    if(intersection.x < 0.0f || intersection.y < 0.0f || intersection.z < 0.0f || intersection.z + intersection.y > 1.0f) 
    {
        return -1.0f; //no intersection
    }
    //ray intersects triangle
    return intersection.x; //return the parameter (t) value along the ray where the intersection occurs
}

float Rectangle::rayIntersection(Ray* ray){ //************OSÄKER PÅ DENNA*************

    // Check if intersection is possible
    if (glm::dot(ray->direction, normal) > 0.0f) {
        return -1.0f; // No intersection possible
    }

    // Define T, P, Q, already have D, E1, E2
    glm::vec3 T = ray->startpoint - vertices[0];
    glm::vec3 P = glm::cross(ray->direction, edge2);
    glm::vec3 Q = glm::cross(T, edge1);

    // Calculate barycentric coordinates of the intersection point
    glm::vec3 intersection = (1.0f / glm::dot(P, edge1)) * glm::vec3(glm::dot(Q, edge2), glm::dot(P, T), glm::dot(Q, ray->direction));

    // Check if the intersection point is within the first triangle (ABD)
    if (intersection.x >= 0.0f && intersection.y >= 0.0f && intersection.z >= 0.0f && intersection.z + intersection.y <= 1.0f) {
        return intersection.x; // Return the parameter (t) value along the ray where the intersection occurs
    }

    // Check if the intersection point is within the second triangle (BCD)
    glm::vec3 T2 = ray->startpoint - vertices[1];
    Q = glm::cross(T2, edge2);
    intersection = (1.0f / glm::dot(P, edge2)) * glm::vec3(glm::dot(Q, edge3), glm::dot(P, T2), glm::dot(Q, ray->direction));

    if (intersection.x >= 0.0f && intersection.y >= 0.0f && intersection.z >= 0.0f && intersection.z + intersection.y <= 1.0f) {
        return intersection.x; // Return the parameter (t) value along the ray where the intersection occurs
    }

    return -1.0f; // No intersection in both triangles
}
