#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
	// first test if ray is parallel to plane, i.e. if ray direction is perpendicular to normal
	// if yes, then return false
	double n_dot_d = normal.dot(ray.direction);
	if (n_dot_d == 0) { // TOLERANCE???
		return false;
	}

	// calculate solution for t
	double q = normal.dot(point);
	t = (q - normal.dot(ray.origin)) / n_dot_d;

	// only return true if t >= min_t (also set n to normal)
	if (t >= min_t) {
		n = normal;
		return true;
	}

	return false;
  ////////////////////////////////////////////////////////////////////////////
}

