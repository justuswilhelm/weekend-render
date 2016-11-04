#include "camera.h"
#include "vec3.h"

Vec3 random_in_unit_disc() {
  Vec3 result;
  do {
    result = Vec3(drand48(), drand48(), 0) * 2.0 - Vec3(1, 1, 0);
  } while (result.dot(result) >= 1.0);
  return result;
}

camera::camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect,
               float aperture, float focus_dist)
    : origin(lookfrom), lens_radius(aperture / 2) {
  float theta = vfov * M_PI / 180;
  float half_height = tan(theta / 2);
  float half_width = aspect * half_height;
  w = (lookfrom - lookat).unit_vector();
  u = vup.cross(w).unit_vector();
  v = w.cross(u);
  lower_left_corner =
      origin - u * half_width * focus_dist - v * half_height * focus_dist - w;
  horizontal = u * 2 * half_width * focus_dist;
  vertical = v * 2 * half_height * focus_dist;
}

Ray camera::get_ray(float s, float t) {
  Vec3 rd = random_in_unit_disc() * lens_radius;
  Vec3 offset = u * rd.x + v * rd.y;
  return Ray(origin + offset, lower_left_corner + horizontal * s +
                                  vertical * t - origin);
}
