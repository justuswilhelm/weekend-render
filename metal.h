#ifndef METAL_H
#define METAL_H
#include "material.h"
#include "ray.h"
#include "vec3.h"

class metal : public material {
public:
  metal(const vec3 &a, float f) : albedo(a), fuzz(f) {}
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       vec3 &attenuation, ray &scattered) const {
    vec3 reflected = r_in.direction().unit_vector().reflect(rec.normal);
    scattered = ray(rec.p, reflected + vec3::random_in_unit_sphere() * fuzz);
    attenuation = albedo;
    return (scattered.direction().dot(rec.normal) > 0);
  }
  vec3 albedo;
  float fuzz;
};
#endif
