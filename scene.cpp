#include "dependencies.hpp"

    void Scene::addPolygon(Polygon* pol){
        polygon.push_back(pol);
    }


    void Scene::rayTarget(Ray& ray) const{

        float clostest_pol = std::numeric_limits<double>::max();

        for(Polygon* pol: this->polygon){
            float X_hit = pol->rayIntersection(&ray);
            if(X_hit > 0.0 && X_hit < clostest_pol){
                clostest_pol = X_hit;
                ray.target = pol;
                ray.setEndpoint(clostest_pol);
            }
        }

    }
    
    void Scene::traceRay(std::shared_ptr<Ray>& root) const {
        std::shared_ptr<Ray> current_pol = root;

        while(true){
            if(current_pol->importance < treshold_importance){
                this ->rayTarget(*current_pol);
                if (current_pol->target == nullptr) break;
                current_pol->is_leaf = true;

                // add ray gets color from material and add to radiance
            }
        }

        // TODO add else if and else statement 

    }
