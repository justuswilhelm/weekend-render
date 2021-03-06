#include "sphere.h"

bool Sphere::hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const {
  auto oc = r.origin() - center;
  auto a = r.direction().dot(r.direction());
  auto b = oc.dot(r.direction());
  auto c = oc.dot(oc) - radius * radius;
  auto discriminant = b * b - a * c;
  auto discriminant_sqrt = sqrt(discriminant);
  if (discriminant > 0) {
    float temp = (-b - discriminant_sqrt) / a;
    if (temp < t_max && temp > t_min) {
      rec.m = m;
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
    temp = (-b + discriminant_sqrt) / a;
    if (temp < t_max && temp > t_min) {
      rec.m = m;
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
  }
  return false;
}
