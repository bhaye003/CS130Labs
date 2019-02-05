#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{

    vec3 vec = ray.endpoint - this -> center;
    vec3 u = ray.direction;
    	
    double a  = dot(u,u);
    double b = 2*dot(vec, u);
    double c = dot(vec, vec) - pow(this -> radius, 2);
    double dis = b*b - 4*a*c;
    double t1, t2;
    if( dis == 0){
	t1 = 0.5 * -b / a;
	t2 = 0;
	
	if(t1 >= small_t){
		return{this, t1, part};
	}
    } 
    else if( dis > 0){
	t1 = 0.5 * (-b + sqrt(dis)) / a;
	t2 = 0.5 * (-b - sqrt(dis)) / a;
	if(t1 >= small_t && t1< t2){
		return{this, t1, part};
	}
	else if(t2 >= small_t && t2 < t1){
		return{this, t2, part};
	}
    }
    return {nullptr,0,part};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = (point - center)/radius;
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
