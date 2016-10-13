#include "camera.h"
#include "float.h"
#include "hitable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"
#include <iostream>
#include <memory>
#include <random>

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = vec3(drand48(), drand48(), drand48()) * 2.0 - vec3(1, 1, 1);
  } while (p.squared_length() >= 1.0);
  return p;
}

vec3 color(const ray &r, hitable &world) {
  hit_record rec;
  if (world.hit(r, 0.001, FLT_MAX, rec)) {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return color(ray(rec.p, target - rec.p), world) * 0.5;
  } else {
    auto unit_direction = r.direction().unit_vector();
    auto t = 0.5 * (unit_direction.y + 1.0);
    return vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
  }
}

int main() {
  auto nx = 400;
  auto ny = 200;
  auto ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  camera cam;

  auto a = std::make_shared<sphere>(sphere(vec3(0, 0, -1), 0.5));
  auto b = std::make_shared<sphere>(sphere(vec3(0, 100.5, -1), 100));
  hitable_list world({a, b});

  for (auto j = 0; j < ny; j++) {
    for (auto i = 0; i < nx; i++) {
      vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        auto u = float(i + drand48()) / float(nx);
        auto v = float(j + drand48()) / float(ny);
        auto r = cam.get_ray(u, v);
        col = col + color(r, world);
      }
      col = col / float(ns);
      col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

      auto ir = int(255 * col.x);
      auto ig = int(255 * col.y);
      auto ib = int(255 * col.z);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
