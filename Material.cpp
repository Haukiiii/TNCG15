#include "dependencies.hpp"

Material::Material() : color{ black } {

	//this->absorption = minimum_absorp + (maximum_absorp - minimum_absorp) * glm::length(color) / glm::length(white);  
}

Material::Material(const glm::dvec3& color) : color{ color }{

}

Material::Material(const glm::dvec3& color, double emittance) : color{ color }{
	
    
}