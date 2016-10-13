#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

class vec3 {
public:
  vec3() {}
  vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  vec3 operator+(const vec3 &v) const;
  vec3 operator-(const vec3 &v) const;
  vec3 operator-() const;
  vec3 operator*(const vec3 &v) const;
  vec3 operator/(const vec3 &v) const;
  vec3 operator*(const float t) const;
  vec3 operator/(const float t) const;

  float dot(const vec3 &v) const;
  vec3 cross(const vec3 &v) const;

  float length() const;
  float squared_length() const;
  vec3 unit_vector() const;

  float x;
  float y;
  float z;
};
