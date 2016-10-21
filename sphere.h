#ifndef SPHERE_H
#define SPHERE_H
#include "hitable.h"
#include "material.h"
#include <memory>

class sphere : public hitable {
public:
  sphere(vec3 cen, float r, std::shared_ptr<material> material)
      : center(cen), radius(r), m(material){};
  virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
  vec3 center;
  float radius;
  std::shared_ptr<material> m;
};
#endif
