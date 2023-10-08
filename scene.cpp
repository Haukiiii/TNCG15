#include "dependencies.hpp"

 //iterates through all objects in the scene, checks for intersections between the ray and each object. keeps track of the closest intersection point found
    void Scene::rayTarget(Ray& ray) const{
        
        float closest_pol = std::numeric_limits<double>::max();

        for(Polygon* pol : this->polygons){
            
            float X_intersection = pol->rayIntersection(&ray); //is -1.0 if there is no intersection (see rayIntersection)
            if(X_intersection > 0.0f && X_intersection < closest_pol){
                closest_pol = X_intersection;
                ray.target = pol;
                ray.setEndpoint(closest_pol);
            }
        }
    }

    void Scene::addBox(Box* box)
    {
        for (size_t i = 0; i < box->triangles.size(); ++i) {
            addPolygon(&box->triangles[i]);
        }
    }

    glm::dvec3 Scene::localLighting(const Ray& incomingRay) const {

        glm::dvec3 terminalRadiance{ black };

        if(incomingRay.target == nullptr) { return terminalRadiance; } //fixes bug when occasionally target is null.******

        // If target is a lightsource simply return color of material
        if(incomingRay.target->material->emittance != 0.0) {
            return incomingRay.target->material->color; 
        }

        for(Polygon* l : lights) //generate shadowrays going to all lightsources 
        {
            glm::dvec3 lightRadiance{ black };

            glm::vec3 startShadow = incomingRay.endpoint + incomingRay.target->CalcUnitNormal(incomingRay.endpoint) * RAY_OFFSET; //startpoint of shadow is the incomingRay endpoint with slight offset to avoid intersection with target
		    std::vector<Ray> shadowrays = l->generateShadowRays(startShadow); //generate shadowray(s)

            //check occlusions by comparing distance to lightsource with distance to closest object in the scene, ignoring other light and transparent objects.
            for(Ray& r : shadowrays) {

                bool lightOccluded{false}; 

                float lightDistance{glm::length(r.endpoint - r.startpoint)}; //TODO vid error ändra direction till endpoint-startpoint

                for(Polygon* geometry : polygons) //check if any geometry in the scene occludes the lightsource
                {
                    Ray compare{r}; //copy shadowray for comparison

                    //make sure other lightsources and transparent objects are ignored 
                    //if(geometry->material->emittance == 0.0)
                    if(dynamic_cast<const LightSource*>(geometry->material) == nullptr || dynamic_cast<const Transparent*>(geometry->material) == nullptr)
                    {
                        float intersection{geometry->rayIntersection(&r)};
                        compare.setEndpoint(intersection);

                        if(intersection > epsilon && lightDistance > glm::length(compare.endpoint - compare.startpoint)) { //TODO vid error ändra direction till endpoint-startpoint
                            lightOccluded = true;
                            break;
                        }   
                    }
                }
                if(!lightOccluded) 
                {

                glm::vec3 targetNormal { incomingRay.target->CalcUnitNormal(incomingRay.endpoint) };
                glm::vec3 lightNormal { l->CalcUnitNormal(incomingRay.endpoint) };
                
                // determinine how much of the incoming light contributes to the radiance at point
                double beta = glm::dot(r.direction, -lightNormal); // how well-aligned shadow ray direction is with the light source's surface normal.
				double alpha = glm::dot(targetNormal, r.direction); // how well-aligned the surface normal is with the shadow ray direction
				double cos_term = alpha * beta; // angle between surface normal and shadow ray direction
				cos_term = glm::max(cos_term, 0.0); // clamp to avoid negative numbers

				double dropoff = glm::pow(glm::length(r.endpoint - r.startpoint), FLUX_DROPOFF); // to account for attenuation of light at distance 

				lightRadiance += l->material->emittance * cos_term * l->material->color / (dropoff * lights.size());
			
                }
                else {
                    //std::cout << "Occlusion occuring" << std::endl; // debugging***
                    //std::cout << "R: " << incomingRay.target->material->color.r << "G: " << incomingRay.target->material->color.g << "B: " << incomingRay.target->material->color.b << std::endl;
                }

            }
            terminalRadiance += (lightRadiance / static_cast<double>(shadowrays.size()));
        }
        return terminalRadiance * incomingRay.target->material->color;
    }
    
    void Scene::traceRay(std::shared_ptr<Ray>& rootRay) const{

        std::shared_ptr<Ray> currentRay = rootRay; //Start at the top of tree-structure

        while(true) 
        {
            // Stop rays of importance below threshold
            if(currentRay->importance < IMPORTANCE_THRESHOLD)
            {
                rayTarget(*currentRay);

                currentRay->is_leaf = true;
                
                currentRay->radiance = localLighting(*currentRay);
                currentRay = currentRay->parent; //move up the tree
            }

            // Ray has no children (no branches yet), generate children
            else if(currentRay->children.size() == 0)
            {
                rayTarget(*currentRay);
                if(currentRay->target == nullptr) { break; } //removes occasional case where target is null (should not be needed, fix bug)

                std::vector<Ray> currentChildren{currentRay->target->material->BRDF(currentRay)}; // Generate child rays based on targets BRDF

                for(Ray& r : currentChildren)
                {
                    r.parent = currentRay;
                    currentRay->children.push_back(std::make_shared<Ray>(r));
                }
            }
            else //Ray is an intermediate node and has children
            {
                bool doCompute{true};

                // If at least one child needs computing, select the first one and sets currentRay to that child, effectively descending further down the tree.
                for(std::shared_ptr<Ray>& c : currentRay->children) 
                {
                    if(!c->is_leaf)
                    {
                        currentRay = c;
                        doCompute = false;
                        break;
                    }
                }
                if(doCompute)
                {
                    currentRay->radiance = localLighting(*currentRay);
                    for(std::shared_ptr<Ray>& c : currentRay->children) 
                    {
                        currentRay->radiance += c->radiance * c->importance / currentRay->importance * 0.8;  
					    c.reset(); //free memory
                    }

                    //currentRay is root Ray
                    if(currentRay->parent == nullptr)
                    {
                        currentRay.reset(); //free memory
                        break;
                    }
                currentRay->is_leaf = true;
                currentRay = currentRay->parent;
                }

            }
        }
    }
