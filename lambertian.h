#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "material.h"
#include "ray.h"
#include "vec3.h"

class lambertian : public material {
public:
  lambertian(const vec3 &a) : albedo(a) {}
  virtual bool scatter(const ray &, const hit_record &rec, vec3 &attenuation,
                       ray &scattered) const {
    vec3 target = rec.p + rec.normal + vec3::random_in_unit_sphere();
    scattered = ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
  }
  vec3 albedo;
};
#endif
