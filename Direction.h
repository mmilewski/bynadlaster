#ifndef __DIRECTION_H_INCLUDED__
#define __DIRECTION_H_INCLUDED__

#include "StdAfx.h"

// Normalized vector. Corresponds to the direction in which the entity
// is going to go
class Direction {
public:
  explicit Direction(double x, double y) {
    Set(x,y);
  }

  void Set(double x, double y) {
    m_x = x;
    m_y = y;
    
    double mag = sqrt(m_x*m_x + m_y*m_y);
    if (mag != 0.0) {
      m_x /= mag;
      m_y /= mag;
    }
  }

  void SetX(double x) { Set(x, m_y); }
  void SetY(double y) { Set(m_x, y); }

  double GetX() const { return m_x; }
  double GetY() const { return m_y; }

  double x() const { return GetX(); }
  double y() const { return GetY(); }

private:
  double m_x;
  double m_y;
};

#endif
