#include "Engine.h"
#include "StdAfx.h"
#include "Bomb.h"
#include "FlameCreator.h"


Bomb::Bomb(size_t owner_id, Position position, int explosion_range)
  : m_anim_frame_num(0), m_position(position), m_time_from_last_frame_switch(.0),
    m_aabb(position-Position(.4,.4), position+Position(.4,.4)),
    m_owner_id(owner_id), m_explision_range(explosion_range), m_living_time(0) {
  SetAliveFlag(true);
}


void Bomb::DoDraw() const {
  if(!IsAlive())
    return;

  const double tile_width_in_px = 16.0;
  const double tile_height_in_px = 16.0;
  TexCoords tc((470.0+tile_width_in_px*m_anim_frame_num), 16.0, tile_width_in_px, tile_height_in_px);
  Engine::Get().Renderer()->DrawSprite(tc, GetPosition());
}


void Bomb::DoUpdate(double dt) {
  if (!IsAlive())
    return;

  // die after time to live
  m_living_time += dt;
  if (m_living_time>=g_bomb_time_to_live)
    Detonate();

  // process animation; change frame if necessary
  const double frame_duration = .3;
  m_time_from_last_frame_switch += dt;
  if( m_time_from_last_frame_switch > frame_duration ) {
    m_anim_frame_num = (m_anim_frame_num+rand()%7)%3;   // choose next frame at random
    m_time_from_last_frame_switch -= frame_duration;
  }
}


void Bomb::Detonate() {
  if(!IsAlive())
    return;
  AddCreator(CreatorPtr(new FlameCreator(m_owner_id, GetPosition(), m_explision_range)));
  SetAliveFlag(false);
}
