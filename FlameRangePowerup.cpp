#include "Engine.h"
#include "Player.h"
#include "FlameRangePowerup.h"
#include "Constants.h"


void FireRangePowerup::DoDraw() const {
  if(!IsAlive()) {
    return;
  }

  const double tile_width_in_px = 16.0;
  const double tile_height_in_px = 16.0;
  const int m_anim_frame_num = 0;
  TexCoords tc((534.0+tile_width_in_px*m_anim_frame_num), 16.0, tile_width_in_px, tile_height_in_px);
  Engine::Get().Renderer()->DrawSpriteInCenter(tc, GetCenterPosition());
  if (g_render_aabbs)
    Engine::Get().Renderer()->DrawAABB(GetAABB());
}


void FireRangePowerup::DoUpdate(double /* dt */) {
  if(!IsAlive())
    return;
}
