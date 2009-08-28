#include "Renderer.h"
#include "StdAfx.h"
#include "Bomb.h"


Bomb::Bomb(Position position)
  : m_anim_frame_num(0), m_position(position) {
}

void Bomb::DoDraw() {
  const double tile_width_in_px = 16.0;
  const double tile_height_in_px = 16.0;
  TexCoords tc((470.0+tile_width_in_px*m_anim_frame_num), 16.0, tile_width_in_px, tile_height_in_px);
  Renderer::Get().DrawSprite(GetPosition(), tc);
}


void Bomb::DoUpdate(double dt) {
}
