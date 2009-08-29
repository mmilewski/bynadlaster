#include "Renderer.h"
#include "StdAfx.h"
#include "Powerup.h"


Powerup::Powerup(Position position)
  : m_position(position), m_aabb(Position(position), Position(position.x+1, position.y+1)) {
  SetAliveFlag(true);
}
