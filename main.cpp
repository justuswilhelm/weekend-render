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

HitableList random_scene() {
  HitableList result;
  int n = 50;
  result.list.push_back(std::make_shared<Sphere>(
      Sphere(Vec3(0, 1000, 0), 1000,
             std::make_shared<Lambertian>(Lambertian(Vec3(0.5, 0.5, 0.5))))));
  for (int i = 0; i < n; i++) {
    float radius = drand48();
    std::shared_ptr<Material> mat;
    auto pos = (Vec3(0.5, 0.5, 0.5) - Vec3::random_vector()) * 10;
    pos.y = -radius;

    if (i % 3 == 0) {
      mat = std::make_shared<Lambertian>(Lambertian(Vec3::random_vector()));
    } else if (i % 3 == 1) {
      mat = std::make_shared<Dielectric>(Dielectric(0.5));
    } else if (i % 3 == 2) {
      mat = std::make_shared<Metal>(Metal(Vec3::random_vector(), 1));
    }
    result.list.push_back(std::make_shared<Sphere>(
                          Sphere(pos, radius, mat)));
  }
  return result;
}

int main() {
  float scale = 1.5;
  int nx(600 * scale);
  int ny(400 * scale);
  auto ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  camera cam(Vec3(-4, -3, 4), Vec3(0, 0, -1), Vec3(0, 1, 0), 90,
             float(nx) / float(ny));
  auto world = random_scene();
  for (auto j = 0; j < ny; j++) {
    fprintf(stderr, "ny: %d/%d\n", j, ny);
    for (auto i = 0; i < nx; i++) {
      Vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u((i + drand48()) / float(nx));
        float v((j + drand48()) / float(ny));
        auto r = cam.get_ray(u, v);
        col = col + color(r, world, 0);
      }
      col = col / float(ns);
      col = Vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

      int ir(255 * col.x);
      int ig(255 * col.y);
      int ib(255 * col.z);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
