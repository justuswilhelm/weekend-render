#include "camera.h"
#include "vec3.h"

camera::camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect)
    : origin(lookfrom) {
  Vec3 u, v, w;
  float theta = vfov * M_PI / 180;
  float half_height = tan(theta / 2);
  float half_width = aspect * half_height;
  w = (lookfrom - lookat).unit_vector();
  u = vup.cross(w).unit_vector();
  v = w.cross(u);
  lower_left_corner = origin - u * half_width - v * half_height - w;
  horizontal = u * 2 * half_width;
  vertical = v * 2 * half_height;
}

Ray camera::get_ray(float u, float v) {
  return Ray(origin,
             lower_left_corner + horizontal * u + vertical * v - origin);
}
