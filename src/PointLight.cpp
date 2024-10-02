#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
	// d should be unit vector; max_t should then be the norm of p - q
	Eigen::Vector3d p_q = p - q;
	d = p_q.normalized();
	max_t = p_q.norm();
  ////////////////////////////////////////////////////////////////////////////
}
