#ifndef __AABB_H_INCLUDED__
#define __AABB_H_INCLUDED__


#include "Position.h"

struct AABB {
  explicit AABB(const Position& min, const Position& max)
    : min(min), max(max) {
  }

  bool CollidesWith(const AABB& other);

  const Position& GetMin() const { return min; }
  const Position& GetMax() const { return max; }

private:
  Position min;
  Position max;
};

#endif
