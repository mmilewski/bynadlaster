#include "Size.h"


std::ostream& operator<< (std::ostream& os, const Size& size) {
  os << '[' << size.width << ", " << size.height << ']';
  return os;
}
