#include "Position.h"
#include <iostream>


std::ostream& operator<< (std::ostream& os, const Position& pos) {
  os << '[' << pos.x << ", " << pos.y << ']';
  return os;
}
