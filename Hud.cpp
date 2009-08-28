#include "Renderer.h"
#include "StdAfx.h"
#include "Hud.h"


void Hud::Draw() {
  Position tile_position(1.5, g_tiles_on_screen_in_y-2);
  Renderer::Get().DrawSprite(tile_position, 
			     TexCoords(1, 172, 254.0, 23.0), 
			     Size((g_tiles_on_screen_in_x - 3)/static_cast<double>(g_tiles_on_screen_in_x),
				  2.0/g_tiles_on_screen_in_y));
}


void Hud::Update(double /* dt */) {

}
