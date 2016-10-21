#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "material.h"
#include "ray.h"
#include "vec3.h"

class Lambertian : public Material {
public:
  Lambertian(const Vec3 &a) : albedo(a) {}
  virtual bool scatter(const Ray &, const HitRecord &rec, Vec3 &attenuation,
                       Ray &scattered) const {
    Vec3 target = rec.p + rec.normal + Vec3::random_in_unit_sphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
  }
  Vec3 albedo;
};
#endif
