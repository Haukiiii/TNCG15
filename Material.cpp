#include "dependencies.hpp"

std::shared_ptr<Ray> Mirror::BRDF(const std::shared_ptr<Ray> &incomingRay) const {

	double importance_reflected{0.0};
	//count all rays in the list of the incoming ray, if rays in list > MAX_RAYS_IN_LIST set importance 0.
	if(incomingRay->countRays()) {
		importance_reflected = incomingRay->importance;
	}
	

	Ray outgoingRay{ incomingRay->endpoint + incomingRay->target->CalcUnitNormal(incomingRay->endpoint) * RAY_OFFSET,	// Startpoint with slight offset
					glm::normalize(glm::reflect(incomingRay->endpoint, incomingRay->target->CalcUnitNormal(incomingRay->endpoint))),	// Perfect reflection (importance in = importance out)
					importance_reflected };

	
	outgoingRay.prev = incomingRay; //set outgoingRay->prev to point to incomingRay.
	incomingRay->next = std::make_shared<Ray>(outgoingRay); //set incomingRay->next to point to outgoingRay.

	return incomingRay->next;

}

Mirror::Mirror()
{
    this->absorption = 0.0;
}

std::shared_ptr<Ray> Diffuse::BRDF(const std::shared_ptr<Ray>& incomingRay) const {
    glm::vec3 Z = incomingRay->target->CalcUnitNormal(incomingRay->endpoint);
    glm::vec3 X = glm::normalize(incomingRay->direction - glm::dot(incomingRay->direction, Z) * Z);
    glm::vec3 Y = normalize(cross(-X, Z));

    // Local coordinates
    glm::mat4 M{ X.x, X.y, X.z, 0.0f,
                 Y.x, Y.y, Y.z, 0.0f,
                 Z.x, Z.y, Z.z, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f };

    std::shared_ptr<Ray> reflected = std::make_shared<Ray>(); // Create a shared_ptr for the output ray

    for (int i = 0; i < DIFF_BOUNCES; ++i) {
        double phi = (static_cast<double>(rand()) / RAND_MAX) * 2 * M_PI;   // [0, 2*PI] around the normal
        double theta = (static_cast<double>(rand()) / RAND_MAX) * M_PI_2;   // [0, PI/2] towards the normal

        // Cartesian coordinates
        float x = cos(phi) * sin(theta);
        float y = sin(phi) * sin(theta);
        float z = cos(theta);
        glm::vec3 local_dir = glm::vec3(x, y, z);

        // Transform direction to world coordinates
        glm::vec3 world_dir = glm::inverse(glm::transpose(M)) * glm::vec4(local_dir, 1.0);

        // Russian Roulette for ref
        double reflected_importance = 0.0;
        if (static_cast<double>(rand()) / RAND_MAX < this->absorption) {
            reflected_importance = incomingRay->importance * this->reflectance / (this->absorption * DIFF_BOUNCES);
        }

        Ray reflected_ray{ incomingRay->endpoint + incomingRay->target->CalcUnitNormal(incomingRay->endpoint) * RAY_OFFSET, world_dir, reflected_importance };

        reflected_ray.depth = incomingRay->depth + 1;

        *reflected = reflected_ray;
    }

    return reflected;
}



std::shared_ptr<Ray> LightSource::BRDF(const std::shared_ptr<Ray>& incomingRay) const {
    double reflected_importance = 0.0;

    Ray stopped{ incomingRay->endpoint, glm::normalize(glm::reflect(incomingRay->endpoint, incomingRay->target->CalcUnitNormal(incomingRay->endpoint))), reflected_importance };

    // Create a shared_ptr to hold the stopped ray
    std::shared_ptr<Ray> result = std::make_shared<Ray>(stopped);

    return result;
}

