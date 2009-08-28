#include "Renderer.h"
#include "StdAfx.h"
#include "Bomb.h"


Bomb::Bomb(Position position)
  : m_anim_frame_num(0), m_position(position), m_time_from_last_frame_switch(.0) {
}

void Bomb::DoDraw() {
  const double tile_width_in_px = 16.0;
  const double tile_height_in_px = 16.0;
  TexCoords tc((470.0+tile_width_in_px*m_anim_frame_num), 16.0, tile_width_in_px, tile_height_in_px);
  Renderer::Get().DrawSprite(GetPosition(), tc);
}

void Bomb::DoUpdate(double dt) {
  // process animation; change frame if necessary
  const double frame_duration = .3;
  m_time_from_last_frame_switch += dt;
  if( m_time_from_last_frame_switch > frame_duration ) {
    m_anim_frame_num = (m_anim_frame_num+rand()%7)%3;   // choose next frame at random
    m_time_from_last_frame_switch -= frame_duration;
  }
}
