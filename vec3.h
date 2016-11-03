#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include <math.h>
#include <stdlib.h>

class Vec3 {
public:
  Vec3() {}
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  static Vec3 random_vector() { return Vec3(drand48(), drand48(), drand48()); }

  static Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
      p = Vec3(drand48(), drand48(), drand48()) * 2.0 - Vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
  }

  Vec3 operator+(const Vec3 &v) const;
  Vec3 operator-(const Vec3 &v) const;
  Vec3 operator-() const;
  Vec3 operator*(const Vec3 &v) const;
  Vec3 operator/(const Vec3 &v) const;
  Vec3 operator*(const float t) const;
  Vec3 operator/(const float t) const;

  Vec3 reflect(const Vec3 &v) { return *this - v * this->dot(v) * 2; }

  float dot(const Vec3 &v) const;
  Vec3 cross(const Vec3 &v) const;

  float length() const;
  float squared_length() const;
  Vec3 unit_vector() const;

  float x;
  float y;
  float z;
};
#endif
