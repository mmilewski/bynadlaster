#include "Renderer.h"
#include "StdAfx.h"
#include "Flame.h"
#include "Engine.h"


Flame::Flame(Position position, Size size, FD::FlameDirection direction)
  : m_position(position),
    m_aabb(position,
           position+Position(size.width*g_tiles_on_screen_in_x, size.height*g_tiles_on_screen_in_y)),
//     m_aabb(position+Position(.1,.1),
//            position+Position(size.width*g_tiles_on_screen_in_x-0.1, size.height*g_tiles_on_screen_in_y-.1)),
    m_size(size),
    m_direction(direction),
    m_anim_frame_num(0),
    m_time_from_last_frame_switch(0.0) {
#warning TODO: above initializing of aabb requires that left-bottom is lower and on the left of the upper right corner. It should be fixed when possible.
  SetAliveFlag(true);
}


void Flame::DoDraw() const {
  if(!IsAlive())
    return;

  const double tile_width_in_px = 16.0;
  const double tile_height_in_px = 16.0;

  TexCoords tc(0,0,0,0);
  if( m_direction==FD::Center )
    tc = TexCoords((390.0+tile_width_in_px*m_anim_frame_num), 48.0, tile_width_in_px, tile_height_in_px);
  else if( m_direction==FD::Left || m_direction==FD::Right)
    tc = TexCoords((326.0+tile_width_in_px*m_anim_frame_num), 48.0, tile_width_in_px, tile_height_in_px);
  else if( m_direction==FD::Up || m_direction==FD::Down )
    tc = TexCoords((582.0+tile_width_in_px*m_anim_frame_num), 32.0, tile_width_in_px, tile_height_in_px);
  else
    assert(false && "Unknown flame direction");

  Engine::Get().Renderer()->DrawSprite(tc, GetPosition(), m_size);
  if (g_render_aabbs)
    Engine::Get().Renderer()->DrawAABB(GetAABB());
}


void Flame::DoUpdate(double dt) {
  if (!IsAlive())
    return;

  // process animation; change frame if necessary
  const double frame_duration = .2;
  m_time_from_last_frame_switch += dt;
  if( m_time_from_last_frame_switch > frame_duration ) {
    m_anim_frame_num++;
    m_time_from_last_frame_switch -= frame_duration;
  }

  if (m_anim_frame_num > 3)
    SetAliveFlag(false);
}
