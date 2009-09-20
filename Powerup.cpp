#include "StdAfx.h"
#include "Powerup.h"


Powerup::Powerup(Position position)
  : m_position(position), m_aabb(position-Position(.5,.5), position+Position(.5,.5)) {
  SetAliveFlag(true);
}
