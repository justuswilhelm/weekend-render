#include "vec3.h"

Vec3 Vec3::operator+(const Vec3 &v) const {
  return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3 &v) const {
  return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

Vec3 Vec3::operator*(const Vec3 &v) const {
  return Vec3(x * v.x, y * v.y, z * v.z);
}

Vec3 Vec3::operator/(const Vec3 &v) const {
  return Vec3(x / v.x, y / v.y, z / v.z);
}

Vec3 Vec3::operator*(const float t) const { return Vec3(x * t, y * t, z * t); }

Vec3 Vec3::operator/(const float t) const {
  auto k = 1.0 / t;
  return Vec3(x * k, y * k, z * k);
}

float Vec3::dot(const Vec3 &v) const {
  return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vec3 Vec3::cross(const Vec3 &v) const {
  return Vec3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.x,
              this->x * v.y - this->y * v.x);
}

float Vec3::length() const { return sqrt(this->squared_length()); }

float Vec3::squared_length() const { return x * x + y * y + z * z; }

Vec3 Vec3::unit_vector() const { return *this / this->length(); }
