#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <iostream>

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////

	//std::cout << "called " << num_recursive_calls << "\n";
	// initialize rgb vector as background colour (black) to output
	rgb = Eigen::Vector3d(0,0,0);

	// 2 base cases: 1) reached max recursion depth, 2) ray has no hits
	// base case 1:
	if (num_recursive_calls > 10) { // arbitrary max recursion depth
		//std::cout << "num rec calls " << num_recursive_calls << "\n";
		return false;
	}

	// if ray hits an object
	int hit_id;
	double t;
	Eigen::Vector3d n;
	if (first_hit(ray, min_t, objects, hit_id, t, n)) {

		// BLINN PHONG SHADING
		rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);

		//std::cout << "bp ";


		// HANDLING MIRROR REFLECTION (if km isn't 0, make recursive call to raycolour)
		Eigen::Vector3d km = ((objects[hit_id])->material)->km;
		if (km.norm() != 0) {

			//std::cout << "mirror\n";

			// calculate reflected ray
			Ray reflected_ray;
			reflected_ray.origin = ray.origin + t * ray.direction; // point of hit
			reflected_ray.direction = reflect(ray.direction, n);

			// initialize mirror contribution colour
			Eigen::Vector3d mirror_rgb; 

			//std::cout << "we are gonna recurse";
			// if reflected ray hits something, then update rgb
			if (raycolor(reflected_ray, 0.0001, objects, lights, num_recursive_calls + 1, mirror_rgb)) {
				rgb += (km.array() * mirror_rgb.array()).matrix();
			}
		}
		return true;
	}
	// base case 2 (no hits) return false
	else {
		return false;
	}
  ////////////////////////////////////////////////////////////////////////////
}
