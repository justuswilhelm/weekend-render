#include <iostream>
#include <memory>
#include <random>

#include "camera.h"
#include "float.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "material.h"
#include "metal.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

vec3 color(const ray &r, hitable &world, int depth) {
  hit_record rec;
  if (world.hit(r, 0.001, FLT_MAX, rec)) {
    ray scattered;
    vec3 attenuation;
    std::shared_ptr<material> m = rec.material;
    if (depth < 50 && m->scatter(r, rec, attenuation, scattered)) {
      return color(scattered, world, depth + 1) * attenuation;
    } else {
      return vec3(0, 0, 0);
    }
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

  auto m1 = std::make_shared<lambertian>(lambertian(vec3(0.8, 0.3, 0.3)));
  auto m2 = std::make_shared<lambertian>(lambertian(vec3(0.8, 0.8, 0.0)));
  auto m3 = std::make_shared<metal>(metal(vec3(0.8, 0.6, 0.2), 0));
  auto m4 = std::make_shared<metal>(metal(vec3(0.8, 0.8, 0.8), 0.3));
  auto a = std::make_shared<sphere>(sphere(vec3(0, 0, -1), 0.5, m1));
  auto b = std::make_shared<sphere>(sphere(vec3(0, 100.5, -1), 100, m2));
  auto c = std::make_shared<sphere>(sphere(vec3(1, 0, -1), 0.5, m3));
  auto d = std::make_shared<sphere>(sphere(vec3(-1, 0, -1), 0.5, m4));
  hitable_list world({a, b, c, d});

  for (auto j = 0; j < ny; j++) {
    for (auto i = 0; i < nx; i++) {
      vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        auto u = float(i + drand48()) / float(nx);
        auto v = float(j + drand48()) / float(ny);
        auto r = cam.get_ray(u, v);
        col = col + color(r, world, 0);
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
