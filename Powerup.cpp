#include "StdAfx.h"
#include "Powerup.h"


Powerup::Powerup(Position position)
  : m_position(position),
    m_aabb(position, position+Position(1,1)) {
  SetAliveFlag(true);
}
