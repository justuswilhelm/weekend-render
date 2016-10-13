#include "float.h"
#include "hitable_list.h"
#include "ray.h"
#include "sphere.h"
#include <random>
#include "vec3.h"
#include "camera.h"
#include <iostream>

vec3 color(const ray &r, hitable *world) {
  hit_record rec;
  if (world->hit(r, 0.0, FLT_MAX, rec)) {
    return vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1) *
           0.5;
  } else {
    auto unit_direction = r.direction().unit_vector();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
  }
}

int main() {
  auto nx = 400;
  auto ny = 200;
  auto ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  camera cam;

  auto *world = new hitable_list({
      new sphere(vec3(0, 0, -1), 0.5),
      new sphere(vec3(0, -100.5, -1), 100)});

  for (auto j = ny - 1; j >= 0; j--) {
    for (auto i = 0; i < nx; i++) {
      vec3 col(0, 0, 0);
      for (int s=0; s < ns; s++) {
        auto u = float(i + drand48()) / float(nx);
        auto v = float(j + drand48()) / float(ny);
        auto r = cam.get_ray(u, v);
        col = col + color(r, world);
      }
      col = col / float(ns);

      auto ir = int(255 * col[0]);
      auto ig = int(255 * col[1]);
      auto ib = int(255 * col[2]);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
