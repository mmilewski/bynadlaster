#ifndef __SIZE_H_INCLUDED__
#define __SIZE_H_INCLUDED__

#include <iostream>


struct Size {
public:
  explicit Size(double width, double height) 
    : width(width), height(height) { 
  }

  friend std::ostream& operator<< (std::ostream& os, const Size& pos);

  double width;
  double height;
};

#endif
