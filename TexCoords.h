#ifndef __TEXCOORDS_H_INCLUDED__
#define __TEXCOORDS_H_INCLUDED__


struct TexCoords {
  explicit TexCoords(double left, double bottom, double width, double height)
    : left(left), bottom(bottom), width(width), height(height) {
    }
  double left;
  double bottom;
  double width;
  double height;
};

#endif
