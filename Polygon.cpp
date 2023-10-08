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
    normal = glm::normalize(glm::cross(edge1, edge2));
}

Box::Box(const glm::vec3& pos, float height, float depth, float width, const Material* material)
{
    corners[0] = pos + glm::vec3(depth * 0.5f, width * -0.5f, height * 0.5f);
    corners[1] = pos + glm::vec3(depth * -0.5f, width * -0.5f, height * 0.5f);
    corners[2] = pos + glm::vec3(depth * -0.5f, width * 0.5f, height * 0.5f);
    corners[3] = pos + glm::vec3(depth * 0.5f, width * 0.5f, height * 0.5f);
    corners[4] = pos + glm::vec3(depth * 0.5f, width * -0.5f, height * -0.5f);
    corners[5] = pos + glm::vec3(depth * -0.5f, width * -0.5f, height * -0.5f);
    corners[6] = pos + glm::vec3(depth * -0.5f, width * 0.5f, height * -0.5f);
    corners[7] = pos + glm::vec3(depth * 0.5f, width * 0.5f, height * -0.5f);

    //Top
    triangles[0] = Triangle(corners[0], corners[3], corners[1], material);
    triangles[1] = Triangle(corners[1], corners[3], corners[2], material);
    //Bottom
    triangles[2] = Triangle(corners[4], corners[5], corners[6], material);
    triangles[3] = Triangle(corners[4], corners[6], corners[7], material);
    //Wall 1
    triangles[4] = Triangle(corners[0], corners[7], corners[3], material);
    triangles[5] = Triangle(corners[0], corners[4], corners[7], material);
    //Wall 2
    triangles[6] = Triangle(corners[0], corners[1], corners[4], material);
    triangles[7] = Triangle(corners[1], corners[5], corners[4], material);
    //Wall 3
    triangles[8] = Triangle(corners[1], corners[2], corners[5], material);
    triangles[9] = Triangle(corners[2], corners[6], corners[5], material);
    //Wall 4
    triangles[10] = Triangle(corners[3], corners[6], corners[2], material);
    triangles[11] = Triangle(corners[3], corners[7], corners[6], material);

}

//--------functions to get the normals of each shape--------//
glm::vec3 Triangle::CalcUnitNormal(const glm::vec3& hit) const { return glm::normalize(glm::cross(this->edge1, this->edge2)); }

glm::vec3 Rectangle::CalcUnitNormal(const glm::vec3& hit) const { return glm::normalize(glm::cross(this->edge1, this->edge2)); }

glm::vec3 Sphere::CalcUnitNormal(const glm::vec3& hit) const { return glm::normalize(hit - this->position); }

//----------Ray intersections implementations (möller trumbore)-------------//
float Triangle::rayIntersection(Ray* ray) const { //lecture 4 möller trumbore 

    //check if intersection is possible (scalar product between raydirection and surface normal must be negative)
    //if(glm::dot(ray->direction, glm::normalize(-normal)) > 0.0f) 
    //{
      //  return -1.0f; //no intersection possible
    //} // this does not work for some reason...
 
    //define T, P, Q, already have D, E1, E2
    glm::vec3 T = (ray->startpoint - vertices[0]);
    glm::vec3 D = ray->direction;
    glm::vec3 P = glm::cross(D, edge2);
    glm::vec3 Q = glm::cross(T, edge1); 

    //calculate barycentric coordinates of the intersection point
    glm::vec3 intersection = (1 / glm::dot(P, edge1)) * glm::vec3(glm::dot(Q, edge2), glm::dot(P, T), glm::dot(Q, D)); 

    //float t = (glm::dot(Q, edge2) / glm::dot(P, edge1)); //t är samma som intersection.x

    //check if the intersection point lies within the triangle
     if(intersection.x < 0.0f || intersection.y < 0.0f || intersection.z < 0.0f || intersection.z + intersection.y > 1.0f) 
    {
        return -1.0f; //no intersection
    } 
    //ray intersects triangle
    return intersection.x; //return the parameter (t) value along the ray where the intersection occurs
}

float Rectangle::rayIntersection(Ray* ray) const { //************OSÄKER PÅ DENNA*************(används inte oavsett)
    std::cout <<"IF U SEE ME I SHOULD NOT BE USED" <<std::endl;
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

float Sphere::rayIntersection(Ray* ray) const
{
    // Follows following theroey viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/

       // A = rayStart, B = rayDirection, C = sphereCenter
       // All dot products for the quadratic formula
    glm::vec3 dot_prods{};

    dot_prods.x = glm::dot(ray->direction, ray->direction);
    dot_prods.y = glm::dot(ray->startpoint - this->position, 2.0f * ray->direction);
    dot_prods.z = glm::dot(ray->startpoint - this->position, ray->startpoint - this->position) - this->radius * this->radius;

    // The dicriminant which check for hits
    float discriminant = dot_prods.y * dot_prods.y / 4.0f - dot_prods.x * dot_prods.z;

    // If determinant < 0: No hit, If ==0, It scraped along the surface
    if (discriminant < epsilon) {
        return -1.0;
    }

    float numerator_neg = -(dot_prods.y / 2.0f * dot_prods.x) - sqrt(discriminant);
    float numerator_pos = -(dot_prods.y / 2.0f * dot_prods.x) + sqrt(discriminant);

    numerator_neg = glm::max(numerator_neg, 0.0f);
    numerator_pos = glm::max(numerator_pos, 0.0f);

    float numerator_true = glm::min(numerator_neg, numerator_pos);

    // Check if hit was behind camera, we dont want that
    if (numerator_true > epsilon)
    {
        return numerator_true;
    }

    return -1.0f;
}

// Generate rays that hits random point on the triangular light source
std::vector<Ray> Triangle::generateShadowRays(const glm::vec3& startpoint) const
{
	std::vector<Ray> shadowrays;
	for (int i = 0; i < AMOUNT_SHADOWRAYS; ++i) {
        //generate random barycentric coordinates
		float u = static_cast<float>(rand() / RAND_MAX);
		float v = (1.0f - u) * (static_cast<float>(rand())) / RAND_MAX;
		glm::vec3 endpoint = vertices[0] * (1.0f - u - v) + vertices[1] * u + vertices[2] * v; // random point on triangular lightsource as endpoint. 
		shadowrays.push_back(Ray{ startpoint, endpoint });
	}
	return shadowrays;
}

std::vector<Ray> Rectangle::generateShadowRays(const glm::vec3& startpoint) const
{
	std::vector<Ray> shadowrays;
	for (int i = 0; i < AMOUNT_SHADOWRAYS; ++i) {
		float u = static_cast<float>(rand() / RAND_MAX);
		float v = (1.0f - u) * (static_cast<float>(rand())) / RAND_MAX;
		glm::vec3 endpoint = this->vertices[0] * (1.0f - u - v) + this->vertices[1] * u + this->vertices[2] * v;
		shadowrays.push_back(Ray{ startpoint, endpoint });
	}
	return shadowrays;
}

std::vector<Ray> Sphere::generateShadowRays(const glm::vec3& start) const
{
    std::vector<Ray> shadow_rays;
    shadow_rays.push_back(Ray{ start, this->position });

    return shadow_rays;
}






