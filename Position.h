#ifndef __POSITION_H_INCLUDED__
#define __POSITION_H_INCLUDED__


#include <boost/operators.hpp>

struct Position : boost::equality_comparable<Position> {

  explicit Position(double x, double y)
    : x(x), y(y) {
  }

  bool operator==(const Position& other)  { return x==other.x && y==other.y; }

  double x;
  double y;
};

#endif
