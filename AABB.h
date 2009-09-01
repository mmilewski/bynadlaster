#ifndef __AABB_H_INCLUDED__
#define __AABB_H_INCLUDED__

#include "StdAfx.h"


struct AABB {
  explicit AABB(const Position& min, const Position& max)
    : min(min), max(max) {
  }

  bool CollidesWith(const AABB& other) const;

  /**
   * Checks whether this includes other.
   */
  bool WhetherIncludes(const AABB& other) const;

  /**
   * Checks for intersection with other AABB taking movement direction into consideration.
   * Movement direction of other object is not considered (static-like object).
   * If inclusion occured, then returns false (no intersection in fact). On intersection
   * return true, else false.
   *
   * @param dir movement direction of _this_ object (not other)
   */
  bool IntersectsUsingDirectionWith(const AABB& other, const Direction& dir) const;

  const Position& GetMin() const { return min; }
  const Position& GetMax() const { return max; }

private:
  Position min;
  Position max;
};

#endif
