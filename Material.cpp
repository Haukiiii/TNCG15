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