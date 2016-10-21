#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H
#include "hitable.h"
#include <memory>
#include <vector>

class HitableList : public Hitable {
public:
  HitableList() {}
  HitableList(std::vector<std::shared_ptr<Hitable>> l) : list(l) {}
  virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
  std::vector<std::shared_ptr<Hitable>> list;
};
#endif
