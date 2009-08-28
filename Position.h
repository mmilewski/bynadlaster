#ifndef __POSITION_H_INCLUDED__
#define __POSITION_H_INCLUDED__


struct Position {

  explicit Position(double x, double y)
    : x(x), y(y) {
    }

  double x;
  double y;
};

#endif
