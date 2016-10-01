#include "vec3.h"

vec3 vec3::operator+(const vec3 &v) const {
  return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
}

vec3 vec3::operator-(const vec3 &v) const {
  return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
}

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }

vec3 vec3::operator*(const vec3 &v) const {
  return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
}

vec3 vec3::operator/(const vec3 &v) const {
  return vec3(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]);
}

vec3 vec3::operator*(const float t) const {
  return vec3(e[0] * t, e[1] * t, e[2] * t);
}

vec3 vec3::operator/(const float t) const {
  auto k = 1.0 / t;
  return vec3(e[0] * k, e[1] * k, e[2] * k);
}

float vec3::dot(const vec3 &v) const {
  return this->e[0] * v.e[0] + this->e[1] * v.e[1] + this->e[2] * v.e[2];
}

vec3 vec3::cross(const vec3 &v) const {
  return vec3(this->e[1] * v.e[2] - this->e[2] * v.e[1],
              this->e[2] * v.e[0] - this->e[0] * v.e[0],
              this->e[0] * v.e[1] - this->e[1] * v.e[0]);
}

float vec3::length() const { return sqrt(this->squared_length()); }

float vec3::squared_length() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

vec3 vec3::unit_vector() const {
  return *this / this->length();
  ;
}

std::istream &operator>>(std::istream &is, vec3 &t) {
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

std::ostream &operator<<(std::ostream &os, vec3 &t) {
  os << t.e[0] << " " << t.e[1] << " " << t.e[2];
  return os;
}
