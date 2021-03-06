#ifndef CAMERA_H
#define CAMERA_H
#include "ray.h"
#include "vec3.h"
#include <cmath>

class camera {
public:
  camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect,
         float aperture, float focus_dist);
  Ray get_ray(float u, float v);

  Vec3 lower_left_corner;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 origin;
  Vec3 u, v, w;
  float lens_radius;
};
#endif
