#ifndef __POSITION_H_INCLUDED__
#define __POSITION_H_INCLUDED__


#include <boost/operators.hpp>

struct Position : boost::equality_comparable<Position>,
                  boost::additive<Position>,
                  boost::subtractable<Position>  {

  explicit Position(double x, double y)
    : x(x), y(y) {
  }

  bool operator==(const Position& other)  { return x==other.x && y==other.y; }

  Position operator+=(const Position& other)  {
    x += other.x;
    y += other.y;
    return *this;
  }

  Position operator-=(const Position& other)  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

//   Position operator/=(double factor) {
//     x /= factor;
//     y /= factor;
//     return *this;
//   }


  double x;
  double y;
};

#endif
