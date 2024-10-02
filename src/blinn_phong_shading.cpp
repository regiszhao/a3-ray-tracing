#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<Object> object = objects[hit_id];
	std::shared_ptr<Material> material = object->material;
	Eigen::Vector3d ka = material->ka;
	Eigen::Vector3d kd = material->kd;
	Eigen::Vector3d ks = material->ks;
	Eigen::Vector3d km = material->km;
	double phong = material->phong_exponent;
	double Ia = 0.1; // ambient light intensity (hard coded)

	// point of hit
	Eigen::Vector3d q = ray.origin + t * ray.direction;
	// view direction is normalized negative ray direction
	Eigen::Vector3d v = (-ray.direction).normalized();

	// L is pixel colour we are returning, initially set to ambient contribution
	Eigen::Vector3d L = Ia * ka;

	// loop through lights
	for (auto light = lights.begin(); light != lights.end(); ++light) {

		// calculate light direction and distance from hit point
		Eigen::Vector3d l;
		double light_max_t;
		(*light)->direction(q, l, light_max_t);

		// if the point is NOT in a shadow caused by this light, then evaluate blinn-phong shading
		Ray shadow_ray;
		shadow_ray.origin = q;
		shadow_ray.direction = l;
		double shadow_min_t = 0.0001; // arbitrary epsilon
		int shadow_hit_id;
		double shadow_t;
		Eigen::Vector3d shadow_n;
		bool shadow_ray_hit = first_hit(shadow_ray, shadow_min_t, objects, shadow_hit_id, shadow_t, shadow_n);
		// point is only in shadow if shadow ray hits an object and object is in front of light (not behind)
		bool point_in_shadow = shadow_ray_hit && (shadow_t < light_max_t); 
		if (!point_in_shadow) { // if point is NOT in shadow
			// get intensity of light
			Eigen::Vector3d I = (*light)->I;
			// calculate half vector
			Eigen::Vector3d h = (v + l).normalized();

			// calculate diffuse contribution
			Eigen::Vector3d diffuse = (kd.array() * I.array()).matrix() * std::max(0.0, n.dot(l));

			// calculate specular contribution
			double n_dot_h_phong = pow(std::max(0.0, n.dot(h)), phong);
			Eigen::Vector3d specular = (ks.array() * I.array()).matrix() * n_dot_h_phong;

			// update L
			L += diffuse + specular;
		}

	}
	
	return L;
  ////////////////////////////////////////////////////////////////////////////
}
