#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
	vec3 color;
	vec3 ambient = ambient + color_ambient * world.ambient_intensity * world.ambient_color;
	vec3 differ;
	vec3 specular;	
	Ray shadowray;
	Light *light_ptr;  



	for(unsigned i = 0; i < world.lights.size(); ++i){
		Hit shadowhit;
		shadowray.endpoint = intersection_point;
		light_ptr = world.lights.at(i);
		vec3 L = light_ptr -> position - intersection_point;
		shadowray.direction = L.normalized();
		shadowhit = world.Closest_Intersection(shadowray);
		if(world.enable_shadows){
			if(shadowhit.object != NULL){
				if(shadowhit.dist >  L.magnitude()){
					double diffMax = std::max(dot(normal.normalized(), -(intersection_point - (light_ptr -> position)).normalized()), 0.0);	
					double specMax = pow(std::max(dot((intersection_point - ray.endpoint).normalized(), (L - 2 * dot(L, normal)*normal).normalized() ), 0.0), specular_power);		  differ = differ + color_diffuse * light_ptr -> Emitted_Light(intersection_point - light_ptr -> position) * diffMax;
					specular = specular + color_specular * light_ptr -> Emitted_Light(intersection_point - light_ptr -> position) * specMax;
				}
			}
			else{
				double diffMax = std::max(dot(normal.normalized(), -(intersection_point - (light_ptr -> position)).normalized()), 0.0);	
				double specMax = pow(std::max(dot((intersection_point - ray.endpoint).normalized(), (L - 2 * dot(L, normal)*normal).normalized() ), 0.0), specular_power);		  differ = differ + color_diffuse * light_ptr -> Emitted_Light(intersection_point - light_ptr -> position) * diffMax;
				specular = specular + color_specular * light_ptr -> Emitted_Light(intersection_point - light_ptr -> position) * specMax;
	
			}
		}
		else{
			
			double diffMax = std::max(dot(normal.normalized(), -(intersection_point - (light_ptr -> position)).normalized()), 0.0);	
			double specMax = pow(std::max(dot((intersection_point - ray.endpoint).normalized(), (L - 2 * dot(L, normal)*normal).normalized() ), 0.0), specular_power);		  differ = differ + color_diffuse * light_ptr -> Emitted_Light(intersection_point - light_ptr -> position) * diffMax;
			specular = specular + color_specular * light_ptr -> Emitted_Light(intersection_point - light_ptr -> position) * specMax;
		}
				
	}
		
		

	color = ambient + differ + specular;
	return color;
}
