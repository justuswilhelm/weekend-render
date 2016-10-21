#ifndef DIELECTRIC_H
#define DIELECTRIC_H
#include "material.h"
#include "ray.h"
#include "vec3.h"

float schlick(float cosine, float ref_idx) {
  float r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool refract(const Vec3 &v, const Vec3 &n, float ni_over_nt, Vec3 &refracted) {
  auto uv = v.unit_vector();
  float dt = uv.dot(n);
  float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0) {
    refracted = (uv - n * dt) * ni_over_nt - n * sqrt(discriminant);
    return true;
  }
  return false;
}

class Dielectric : public Material {
public:
  Dielectric(float ri) : ref_idx(ri) {}
  virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation,
                       Ray &scattered) const {
    float ni_over_nt;
    float reflect_prob;
    float cosine;

    auto reflected = r_in.direction().reflect(rec.normal);
    Vec3 outward_normal;
    attenuation = Vec3(1.0, 1.0, 1.0);
    Vec3 refracted;

    if (r_in.direction().dot(rec.normal) > 0) {
      outward_normal = -rec.normal;
      ni_over_nt = ref_idx;
      cosine = ref_idx * r_in.direction().dot(rec.normal) /
               r_in.direction().length();
    } else {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / ref_idx;
      cosine = -r_in.direction().dot(rec.normal) / r_in.direction().length();
    }
    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
      reflect_prob = schlick(cosine, ref_idx);
    } else {
      scattered = Ray(rec.p, reflected);
      reflect_prob = 1.0;
    }
    if (drand48() < reflect_prob) {
      scattered = Ray(rec.p, reflected);
    } else {
      scattered = Ray(rec.p, refracted);
    }
    return true;
  }
  float ref_idx;
};
#endif
