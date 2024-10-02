#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////

	bool hit = false; // whether or not there was a hit
	t = -1; // first hit t value, will be output
	double cur_t; // current t value, updates every loop
	Eigen::Vector3d cur_n; // current n value, updates every loop
	int index = -1;

	// loop through objects, if found new min, update t and n and hit_id
	for (auto obj = objects.begin(); obj != objects.end(); ++obj) {

		index += 1;

		// if Object.intersect returns true (hits object) 
		if ((**obj).intersect(ray, min_t, cur_t, cur_n)) {
			hit = true;
			// if t < cur_t OR cur_t == -1: update variables
			if ((t == -1) || (cur_t < t)) {
				t = cur_t;
				n = cur_n;
				hit_id = index;
			}
		}
	}

	return hit;
  ////////////////////////////////////////////////////////////////////////////
}
