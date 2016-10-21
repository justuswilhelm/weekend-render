#ifndef METAL_H
#define METAL_H
#include "material.h"
#include "ray.h"
#include "vec3.h"

class Metal : public Material {
public:
  Metal(const Vec3 &a, float f) : albedo(a), fuzz(f) {}
  virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation,
                       Ray &scattered) const {
    Vec3 reflected = r_in.direction().unit_vector().reflect(rec.normal);
    scattered = Ray(rec.p, reflected + Vec3::random_in_unit_sphere() * fuzz);
    attenuation = albedo;
    return (scattered.direction().dot(rec.normal) > 0);
  }
  Vec3 albedo;
  float fuzz;
};
#endif
