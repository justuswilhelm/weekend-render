#include "ray.h"
#include "vec3.h"
#include <iostream>

vec3 color(const ray &r) {
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
