#include "viewing_ray.h"

void coord_to_camera(
	const int i,
	const int j,
	const int n_x,
	const int n_y,
	const double width,
	const double height,
	double& u,
	double& v
);

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
	// ray origin is camera eye (e)
	ray.origin = camera.e;

	// find coordinate of pixel j, i, subtract e from it -> ray direction
	double u;
	double v;
	coord_to_camera(i, j, width, height, camera.width, camera.height, u, v);
	Eigen::Vector3d u_pos = u * camera.u;
	Eigen::Vector3d v_pos = v * camera.v;
	// to calculate w_pos: w = e - d*w
	Eigen::Vector3d w_pos = camera.e - camera.d * camera.w;
	Eigen::Vector3d s = u_pos + v_pos + w_pos;
	ray.direction = s - camera.e;
	//std::cout << "ray direction = " << ray.direction << "\n";
  ////////////////////////////////////////////////////////////////////////////
}



// make helper function, takes coordinates in image, returns u, v coordinates
// u = (width * (j + 1/2) / n_x) - width/2
// v = - ( (height * (i + 1/2) / n_y) - height/2 )  // turn everything negative since pixel coordinate is at top left
void coord_to_camera(
	const int i,
	const int j,
	const int n_x, // number of pixels in x direction
	const int n_y, // number of pixels in y direction
	double width, // width in world space
	double height, // height in world space
	double& u,
	double& v
) {
	u = (width * (j + 1 / 2) / n_x) - width / 2;
	v = -((height * (i + 1 / 2) / n_y) - height / 2);
}

