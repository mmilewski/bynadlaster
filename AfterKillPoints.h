#ifndef __AFTER_KILL_POINTS_H_INCLUDED__
#define __AFTER_KILL_POINTS_H_INCLUDED__


#include "StdAfx.h"
#include "NonEntity.h"


class AfterKillPoints : public NonEntity {
public:
  enum Amount {
    _100,
    _200,
    _400,
    _800,
    _1600,
    _3200,
    _6400,
    _1000,
    _2000,
    _4000,
    _8000
  };


public:
  explicit AfterKillPoints(Position start_position, Amount amount, size_t duration = s_life_time);
  

protected:
  void DoDraw() const;
  void DoUpdate(double dt);  


private:
  Position m_position;
  Size m_size;
  Amount m_amount;
  double m_time_left;
  
private:
  static double s_life_time;
  
};


#endif
