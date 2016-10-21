#include <iostream>
#include <memory>
#include <random>

#include "camera.h"
#include "dielectric.h"
#include "float.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "material.h"
#include "metal.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

Vec3 color(const Ray &r, Hitable &world, int depth) {
  HitRecord rec;
  if (world.hit(r, 0.001, FLT_MAX, rec)) {
    Ray scattered;
    Vec3 attenuation;
    std::shared_ptr<Material> m = rec.m;
    if (depth < 50 && m->scatter(r, rec, attenuation, scattered)) {
      return color(scattered, world, depth + 1) * attenuation;
    } else {
      return Vec3(0, 0, 0);
    }
  } else {
    auto unit_direction = r.direction().unit_vector();
    auto t = 0.5 * (unit_direction.y + 1.0);
    return Vec3(1.0, 1.0, 1.0) * (1.0 - t) + Vec3(0.5, 0.7, 1.0) * t;
  }
}

int main() {
  auto nx = 400;
  auto ny = 200;
  auto ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  camera cam;

  HitableList world({
      std::make_shared<Sphere>(Sphere(
          Vec3(0, 0, -1), 0.5,
          std::make_shared<Lambertian>(Lambertian(Vec3(0.1, 0.2, 0.5))))),
      std::make_shared<Sphere>(Sphere(
          Vec3(0, 100.5, -1), 100,
          std::make_shared<Lambertian>(Lambertian(Vec3(0.8, 0.8, 0.0))))),
      std::make_shared<Sphere>(
          Sphere(Vec3(1, 0, -1), 0.5,
                 std::make_shared<Metal>(Metal(Vec3(0.8, 0.6, 0.2), 0)))),
      std::make_shared<Sphere>(Sphere(
          Vec3(-1, 0, -1), 0.5, std::make_shared<Dielectric>(Dielectric(1.5)))),
      std::make_shared<Sphere>(
          Sphere(Vec3(-1, 0, -1), -0.45,
                 std::make_shared<Dielectric>(Dielectric(1.5)))),
  });

  for (auto j = 0; j < ny; j++) {
    for (auto i = 0; i < nx; i++) {
      Vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        auto u = float(i + drand48()) / float(nx);
        auto v = float(j + drand48()) / float(ny);
        auto r = cam.get_ray(u, v);
        col = col + color(r, world, 0);
      }
      col = col / float(ns);
      col = Vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

      auto ir = int(255 * col.x);
      auto ig = int(255 * col.y);
      auto ib = int(255 * col.z);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
