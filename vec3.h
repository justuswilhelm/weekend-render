#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>

class vec3 {
public:
  vec3() {}
  vec3(float e0, float e1, float e2) {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
  }
  float x() const { return e[0]; }
  float y() const { return e[1]; }
  float z() const { return e[2]; }
  float r() const { return e[0]; }
  float g() const { return e[1]; }
  float b() const { return e[2]; }

  float operator[](int i) const { return e[i]; }

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

  float e[3];
};
