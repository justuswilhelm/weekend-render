#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "material.h"
#include <memory>

class Sphere : public Hitable {
public:
  Sphere(Vec3 cen, float r, std::shared_ptr<Material> material)
      : center(cen), radius(r), m(material){};
  virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
  Vec3 center;
  float radius;
  std::shared_ptr<Material> m;
};
#endif
