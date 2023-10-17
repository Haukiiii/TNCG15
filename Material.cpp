#include "dependencies.hpp"



//--------------BRDF IMPLEMENTATION--------------//

std::vector<Ray> Mirror::BRDF(const std::shared_ptr<Ray> &incomingRay) const {

	double importance_outgoing{0.0};
	// depth > MAX_RAYS_IN_LIST set importance 0.
	if(incomingRay->depth < MAX_DEPTH) { importance_outgoing = incomingRay->importance; }
	
	Ray outgoingRay{ incomingRay->endpoint + incomingRay->target->CalcUnitNormal(incomingRay->endpoint) * RAY_OFFSET,	// Startpoint with slight offset to avoid self-intersections
					glm::normalize(glm::reflect(incomingRay->endpoint, incomingRay->target->CalcUnitNormal(incomingRay->endpoint))),	// Perfect reflection (importance in = importance out)
					importance_outgoing };

	outgoingRay.depth = (incomingRay->depth + 1);
    std::vector<Ray> outgoing;
    outgoing.push_back(outgoingRay);
	
	return outgoing;

}

std::vector<Ray> Diffuse::BRDF(const std::shared_ptr<Ray>& incomingRay) const {
    //get local coordinates for the surface being shaded by creating orthogonal vectors X,Y,Z
    glm::vec3 Z = incomingRay->target->CalcUnitNormal(incomingRay->endpoint); // surface normal
    glm::vec3 X = glm::normalize(incomingRay->direction - glm::dot(incomingRay->direction, Z) * Z); 
    glm::vec3 Y = glm::normalize(glm::cross(-X, Z));

    // Local to World transformation matrix
    glm::mat4 L_2_W{ X.x, X.y, X.z, 0.0f,
                     Y.x, Y.y, Y.z, 0.0f,
                     Z.x, Z.y, Z.z, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f };

    std::vector<Ray> outgoing; // to store outgoing/reflected rays.

    //Simulate diffuse bounces, each iteration of the loop generates a random local direction in spherical coordinates
    for (int i = 0; i < DIFF_BOUNCES; ++i) {
        float phi = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * static_cast<float>(M_PI);   // [0, 2*PI] around the normal (azimuth)
        float omega = (static_cast<float>(rand()) / RAND_MAX) *  static_cast<float>(M_PI_2);   // [0, PI/2] towards the normal (inclination)

        // convert Spherical coordinates to cartesian coordinates
        float x{cos(phi) * sin(omega)};
        float y{sin(phi) * sin(omega)};
        float z{cos(omega)};
        glm::vec3 localDirection{x, y, z};
        // Transform direction to world coordinates
        glm::vec3 worldDirection = glm::inverse(glm::transpose(L_2_W)) * glm::vec4(localDirection, 1.0f);        

        double importance_outgoing{0.0};

        // Russian Roulette termination for ref
        // Generate random number between [0,1], if greater than the specified absorption, the ray reflection is considered, otherwise reflection is terminated. 
        
        if (static_cast<double>(rand()) / RAND_MAX > this->absorption) {
            importance_outgoing = incomingRay->importance * this->reflectance / (this->absorption * DIFF_BOUNCES);
        }

        Ray outgoingRay{ incomingRay->endpoint + incomingRay->target->CalcUnitNormal(incomingRay->endpoint) * RAY_OFFSET, //// Startpoint with slight offset to avoid self-intersections
                         worldDirection, importance_outgoing }; 

        outgoingRay.depth = (incomingRay->depth + 1);
        outgoing.push_back(outgoingRay);
    }

    return outgoing;
}

std::vector<Ray> LightSource::BRDF(const std::shared_ptr<Ray>& incomingRay) const {
    double importance_outgoing{0.0}; 

    Ray stopped{ incomingRay->endpoint, // outgoing ray (stopped) starts at the same point where the incoming ray ends.
                glm::normalize(glm::reflect(incomingRay->endpoint, incomingRay->target->CalcUnitNormal(incomingRay->endpoint))), 
                importance_outgoing };

    stopped.depth = (incomingRay->depth + 1);
    std::vector<Ray> outgoing;
    outgoing.push_back(stopped);

    return outgoing;
}


std::vector<Ray> Transparent::BRDF(const std::shared_ptr<Ray>& incomingRay) const
{
	double importance_reflected{ 0.0 };
	double importance_refracted{ 0.0 };

	glm::vec3 N = incomingRay->inside_transparent_object ? -incomingRay->target->CalcUnitNormal(incomingRay->endpoint) : incomingRay->target->CalcUnitNormal(incomingRay->endpoint); // Switch normal depending on inside or outside of object.
	glm::vec3 I = incomingRay->direction;

	double cos_omega = glm::dot(-I, N); 
	double omega = glm::acos(cos_omega); // incident angle of the incoming ray

	double max_angle = glm::asin(REFLECTIVE_INDEX_AIR / this->reflective_index); // Max angle that refraction can occur

	if (incomingRay->depth < MAX_DEPTH)
	{

		if (incomingRay->inside_transparent_object && omega > max_angle) // total internal reflection
		{
			importance_reflected = incomingRay->importance;
		}
		else
		{
			// Schlicks equation
			double R0 = incomingRay->inside_transparent_object ?
				glm::pow(((this->reflective_index - REFLECTIVE_INDEX_AIR) / (REFLECTIVE_INDEX_AIR + this->reflective_index)), 2.0)
				: glm::pow(((REFLECTIVE_INDEX_AIR - this->reflective_index) / (REFLECTIVE_INDEX_AIR + this->reflective_index)), 2.0);
			// The brdfs of the reflected and refracted rays
			importance_reflected = (R0 + (1.0 - R0) * glm::pow((1.0 - cos_omega), 5.0)) * incomingRay->importance;
			importance_refracted = (1.0 - importance_reflected) * incomingRay->importance;
		}
	}
	
	Ray reflected_ray{ incomingRay->endpoint + N * RAY_OFFSET,	// Start with offset
				glm::normalize(glm::reflect(incomingRay->endpoint, N)),
				importance_reflected };

	float R = incomingRay->inside_transparent_object ? this->reflective_index / REFLECTIVE_INDEX_AIR : REFLECTIVE_INDEX_AIR / this->reflective_index; // The ratio of the refractive indicies, depending on inside or outside object
	glm::vec3 refracted_direction = R * I + N * (-R * glm::dot(N, I) // Here we could also use glm::refract(I, N, R)
		- glm::sqrt(1.0f - glm::pow(R, 2.0f) * (1.0f - glm::pow(glm::dot(N, I), 2.0f))));

	glm::vec3 refracted_start = incomingRay->endpoint - N * RAY_OFFSET;

	Ray refracted_ray{ refracted_start, refracted_direction, importance_refracted };

	// set inside or outside state of the ray
	reflected_ray.inside_transparent_object = incomingRay->inside_transparent_object;
	refracted_ray.inside_transparent_object = !incomingRay->inside_transparent_object;

	reflected_ray.depth = (incomingRay->depth + 1);
	refracted_ray.depth = (incomingRay->depth + 1);

	std::vector<Ray> result;
	result.push_back(reflected_ray);
	result.push_back(refracted_ray);

	return result;
}
