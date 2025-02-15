#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
	d = (-DirectionalLight::d).normalized();
	max_t = std::numeric_limits<double>::infinity();
  ////////////////////////////////////////////////////////////////////////////
}

