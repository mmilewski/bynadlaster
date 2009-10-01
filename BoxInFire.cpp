#include "Engine.h"
#include "BoxInFire.h"


BoxInFire::BoxInFire(Position position)
  : m_position(position),
    m_anim_frames_count(6),
    m_frame_duration_time(.5/m_anim_frames_count),  // 1.2 magic constant is desired animation duration time
    m_current_anim_frame(0),
    m_current_frame_duration_time(0)  {
}


void BoxInFire::DoDraw() const {
  if (!IsAlive()) {
    return;
  }

  TexCoords tc(495 + 16 * m_current_anim_frame, 142, 16, 16);
  Engine::Get().Renderer()->DrawSprite(tc, m_position);
}


void BoxInFire::DoUpdate(double dt) {
  if (!IsAlive()) {
    return;
  }

  m_current_frame_duration_time += dt;
  while (m_current_frame_duration_time > m_frame_duration_time) {
    m_current_frame_duration_time -= m_frame_duration_time;
    m_current_anim_frame++;
  }

  if (m_current_anim_frame > m_anim_frames_count) {
    SetAliveFlag(false);
  }
}
