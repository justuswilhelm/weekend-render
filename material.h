#ifndef MATERIAL_H
#define MATERIAL_H
#include "hitable.h"
#include "ray.h"
#include "vec3.h"

class Material {
public:
  virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation,
                       Ray &scattered) const = 0;
};
#endif
