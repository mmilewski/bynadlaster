#include "Player.h"
#include "Renderer.h"
#include "BombPowerup.h"


void BombPowerup::DoDraw() {
  if(!IsAlive())
    return;

  const double tile_width_in_px = 16.0;
  const double tile_height_in_px = 16.0;
  const int m_anim_frame_num = 0;
  TexCoords tc((518.0+tile_width_in_px*m_anim_frame_num), 16.0, tile_width_in_px, tile_height_in_px);
  Renderer::Get().DrawSprite(GetPosition(), tc);
}


void BombPowerup::DoUpdate(double /* dt */) {
  if(!IsAlive())
    return;
}
