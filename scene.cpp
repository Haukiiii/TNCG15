#include "dependencies.hpp"

    void Scene::addPolygon(Polygon* pol){
        polygons.push_back(pol);
    }

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
    
    void Scene::traceRay(std::shared_ptr<Ray>& head) const {
        std::shared_ptr<Ray> currentRay = head;
        while(true)
        {
            //No reflections --> generate reflection rays
            if(currentRay->next == nullptr){
                this->rayTarget(*currentRay); //get closest intersection
                if(currentRay->target == nullptr) {break;} //avoid bug..?

                currentRay->next = currentRay->target->material->BRDF(currentRay); //ray generated based on the material's BRDF
                //currentRay->next->prev = std::make_shared<Ray>(currentRay); //link nodes (kanske inte behövs?)****
            }   
            else //currentRay has reflections, can be intermidiate node in the list.
            {
                bool evaluate{true};
                while(currentRay != nullptr) {
                    if(currentRay->next != nullptr) { //currentRay needs evaluation
                        currentRay = currentRay->next; //move along the list of rays
                        evaluate = false;
                        break;
                    }
                }

                if(evaluate) {
                    while(currentRay->next != nullptr){
                        currentRay->radiance += currentRay->next->radiance;
                        currentRay = currentRay->next; 
                        currentRay->next.reset();
                    }
                    if(currentRay == nullptr){
                        currentRay.reset();
                        break;
                    }
                    currentRay = currentRay->prev;
                }
                
            }
        }
    }


      /*   while(true){
            if(current_pol->importance < treshold_importance){
                this ->rayTarget(*current_pol);
                if (current_pol->target == nullptr) break;
                current_pol->is_leaf = true;

                // add ray gets color from material and add to radiance
            }
        } */

        // TODO add else if and else statement 

    /*
    void Scene::traceRay(std::shared_ptr<Ray>& root) const
{
    std::shared_ptr<Ray> current = root;

    while (true)
    {
        // Sets color from local lighting for leaf node
        if (current->importance < threshold_importance)
        {
            rayTarget(*current);

            if (current->target == nullptr)
            {
                break;
            }
            current->is_leaf = true;

            glm::dvec3 local_color = localLighting(*current);
            current->radiance = glm::length(local_color);
            current->color = local_color;
            current = current->prev;  // Assuming you have a 'prev' member in the Ray class
        }
        // Create child rays if there are none and current isn't a leaf node
        else if (current->next == nullptr)
        {
            rayTarget(*current);

            if (current->target == nullptr)
            {
                break;
            }
            std::vector<Ray> child_rays = current->target->material->brdf(*current);

            for (Ray& r : child_rays)
            {
                r.prev = current;
                current->next = std::make_shared<Ray>(r);
                current = current->next;
            }
        }
        // Iterate through the child nodes, if they are all leaves, evaluate color, delete children, make current a leaf and set current to parent.
        // If a child branch is not yet evaluated, evaluate that branch by setting current to that child.
        else
        {
            bool evaluate = true;
            std::shared_ptr<Ray> temp;

            while (current->next != nullptr)
            {
                temp = current->next;
                // if evaluation of child branch is needed
                if (!temp->is_leaf)
                {
                    current = temp;
                    evaluate = false;
                    break;
                }
                current = temp;
            }

            if (evaluate)
            {
                glm::dvec3 local_color = localLighting(*current);
                current->radiance = glm::length(local_color);

                current = current->prev;  // Move back to the parent
                while (current->next != nullptr)
                {
                    current->radiance += current->next->radiance * current->next->importance / current->importance;
                    current = current->next;
                }

                current = current->prev;  // Move back to the parent
                current->color = local_color * current->radiance;
                while (current->next != nullptr)
                {
                    current->color += current->next->color * g_color_contribution;
                    current->next.reset();
                    current = current->prev;
                }

                // Reached the root
                if (current->prev == nullptr)
                {
                    current.reset();  // Current and root points to the same ray, delete the extra node
                    break;
                    // End
                }
                current->is_leaf = true;
                current = current->prev;
            }
        }
    }
}
    */