#include "vec3.h"

vec3 vec3::operator+(const vec3 &v) const {
  return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator-(const vec3 &v) const {
  return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator-() const { return vec3(-x, -y, -z); }

vec3 vec3::operator*(const vec3 &v) const {
  return vec3(x * v.x, y * v.y, z * v.z);
}

vec3 vec3::operator/(const vec3 &v) const {
  return vec3(x / v.x, y / v.y, z / v.z);
}

vec3 vec3::operator*(const float t) const { return vec3(x * t, y * t, z * t); }

vec3 vec3::operator/(const float t) const {
  auto k = 1.0 / t;
  return vec3(x * k, y * k, z * k);
}

float vec3::dot(const vec3 &v) const {
  return this->x * v.x + this->y * v.y + this->z * v.z;
}

vec3 vec3::cross(const vec3 &v) const {
  return vec3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.x,
              this->x * v.y - this->y * v.x);
}

float vec3::length() const { return sqrt(this->squared_length()); }

float vec3::squared_length() const { return x * x + y * y + z * z; }

vec3 vec3::unit_vector() const {
  return *this / this->length();
  ;
}

std::istream &operator>>(std::istream &is, vec3 &t) {
  is >> t.x >> t.y >> t.z;
  return is;
}

std::ostream &operator<<(std::ostream &os, vec3 &t) {
  os << t.x << " " << t.y << " " << t.z;
  return os;
}
