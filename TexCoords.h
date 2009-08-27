#ifndef __TEXCOORDS_H_INCLUDED__
#define __TEXCOORDS_H_INCLUDED__


struct TexCoords {
  explicit TexCoords(double bottom, double left, double right, double top)
    : bottom(bottom), left(left), right(right), top(top) {
    }
  double bottom;
  double left;
  double right;
  double top;
};

#endif
