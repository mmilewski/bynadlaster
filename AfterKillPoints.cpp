#include "Renderer.h"
#include "AfterKillPoints.h"


double AfterKillPoints::s_life_time = 2.5;

AfterKillPoints::AfterKillPoints(Position start_position, Amount amount, size_t duration)
  : m_position(start_position),
    m_size(Size(0.02, 0.02)),
    m_amount(amount),
    m_time_left(duration) {
}

  
void AfterKillPoints::DoDraw() const {
  if (!IsAlive()) {
    return;
  }
  
  TexCoords tc(442 + m_amount * 16, 389, 16, 5);
  double opacity = m_time_left / s_life_time * 2.0; // we want max opacity for some time
  if (opacity > 1.0) opacity = 1.0;
  Renderer::Get().DrawSpriteAbsolute(m_position, tc, Color(1,1,0,opacity), m_size);
}


void AfterKillPoints::DoUpdate(double dt) {
  if (!IsAlive()) {
    return;
  }

  m_position.y += dt * 0.015;

  if (m_time_left < 0.5) {
    m_position.x -= dt * 0.006;
  }
  else if (m_time_left < 1.0) {
    m_position.x += dt * 0.006;
  }

  m_time_left -= dt;
  if (m_time_left < 0.0) {
    SetAliveFlag(false);
  }
}  
