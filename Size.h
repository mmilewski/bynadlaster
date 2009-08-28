#ifndef __SIZE_H_INCLUDED__
#define __SIZE_H_INCLUDED__

struct Size {
public:
  explicit Size(double width, double height) 
    : width(width), height(height) { 
  }

  double width;
  double height;
};

#endif
