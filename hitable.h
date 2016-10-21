#ifndef HITABLE_H
#define HITABLE_H
#include "ray.h"
#include <memory>

class Material;

struct HitRecord {
  float t;
  Vec3 p;
  Vec3 normal;
  std::shared_ptr<Material> m;
};

class Hitable {
public:
  virtual bool hit(const Ray &r, float t_min, float t_max,
                   HitRecord &rec) const = 0;
};
#endif
