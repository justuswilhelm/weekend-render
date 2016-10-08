#include "ray.h"
#include "vec3.h"
#include <iostream>

bool hit_sphere(const vec3 &center, float radius, const ray &r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().dot(r.direction());
  auto b = oc.dot(r.direction()) * 2.0;
  auto c = oc.dot(oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}

vec3 color(const ray &r) {
  if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
    return vec3(1, 0, 0);
  }
  auto unit_direction = r.direction().unit_vector();
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return vec3(1.0, 1.0, 1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t;
}

int main() {
  auto nx = 200;
  auto ny = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  for (auto j = ny - 1; j >= 0; j--) {
    for (auto i = 0; i < nx; i++) {
      auto u = float(i) / float(nx);
      auto v = float(j) / float(ny);
      ray r(origin, lower_left_corner + horizontal * u + vertical * v);
      auto col = color(r);

      auto ir = int(255.99 * col[0]);
      auto ig = int(255.99 * col[1]);
      auto ib = int(255.99 * col[2]);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
