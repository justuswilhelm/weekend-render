#pragma once
#include "hitable.h"
#include <vector>

class hitable_list : public hitable {
public:
  hitable_list() {}
  hitable_list(std::vector<hitable *> l) : list(l) {}
  virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
  std::vector<hitable *> list;
};
