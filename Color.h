#ifndef __COLOR_H_INCLUDED__
#define __COLOR_H_INCLUDED__


struct Color {
  explicit Color(double r, double g, double b, double a = 1.0) 
    : r(r), g(g), b(b), a(a) {
  }

  double r;
  double g;
  double b;
  double a;
};


#endif
