#ifndef __POSITION_H_INCLUDED__
#define __POSITION_H_INCLUDED__


struct Position {

  explicit Position(double x, double y, double width, double height)
    : x(x), y(y), width(width), height(height) {
    }

  double x;
  double y;
  double width;
  double height;
};

#endif
