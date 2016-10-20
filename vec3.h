#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include <math.h>
#include <stdlib.h>

class vec3 {
public:
  vec3() {}
  vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  static vec3 random_in_unit_sphere() {
    vec3 p;
    do {
      p = vec3(drand48(), drand48(), drand48()) * 2.0 - vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
  }

  vec3 operator+(const vec3 &v) const;
  vec3 operator-(const vec3 &v) const;
  vec3 operator-() const;
  vec3 operator*(const vec3 &v) const;
  vec3 operator/(const vec3 &v) const;
  vec3 operator*(const float t) const;
  vec3 operator/(const float t) const;

  vec3 reflect(const vec3 &v) { return *this - v * this->dot(v) * 2; }

  float dot(const vec3 &v) const;
  vec3 cross(const vec3 &v) const;

  float length() const;
  float squared_length() const;
  vec3 unit_vector() const;

  float x;
  float y;
  float z;
};
#endif
