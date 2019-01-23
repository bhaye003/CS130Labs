#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    double a  = 1;
    double b = 2*dot( ray.direction, ray.endpoint - center);
    double c = dot(ray.endpoint - center, ray.endpoint - center) - radius*radius;
    double dis = b*b - 4*a*c;
    double t = 0, t0 = 0, t1 = 0;
    if( dis == 0){
	t = 0.5 * -b / a;
    } 
    else if( dis > 0){
	t0 = 0.5 * (-b + sqrt(dis)) / a;
	t1 = 0.5 * (-b + sqrt(dis)) / a;
	t = (t0 >= t1)  ? t0 : t1;
    }
    if(t >= small_t) {
	return{this, t, part};
    }


    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
