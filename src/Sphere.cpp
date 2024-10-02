#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
	// calculate quadratic coefficients
	Eigen::Vector3d e_c = ray.origin - center;
	double a = (ray.direction).dot(ray.direction);
	double b = 2 * (ray.direction).dot(e_c);
	double c = e_c.dot(e_c) - pow(radius, 2);

	// calculate discriminant
	double D = pow(b, 2) - (4 * a * c);

	// if discriminant is negative, no hits, return false
	if (D < 0) { // TOLERANCE?
		return false;
	}

	// calculate solution for t
	double t_1 = (-b + sqrt(D)) / (2 * a);
	double t_2 = (-b - sqrt(D)) / (2 * a);

	// if both solutions are less than min_t, no hits, return false
	if ((t_1 < min_t) && (t_2 < min_t)) {
		return false;
	}
	// if both solutions are valid, set t = minimum t
	else if ((t_1 >= min_t) && (t_2 >= min_t)) {
		t = std::min(t_1, t_2);
	}
	// if only one solution is valid, set t to valid solution
	else {
		t = (t_1 >= min_t) ? t_1 : t_2;
	}

	// calculate normal
	Eigen::Vector3d p = ray.origin + t * ray.direction;
	n = (p - center) / radius;

	return true;
  ////////////////////////////////////////////////////////////////////////////
}

