#ifndef HITABLE_H
#define HITABLE_H
#include "ray.h"
#include <memory>

class material;

struct hit_record {
  float t;
  vec3 p;
  vec3 normal;
  std::shared_ptr<material> m;
};

class hitable {
public:
  virtual bool hit(const ray &r, float t_min, float t_max,
                   hit_record &rec) const = 0;
};
#endif
