#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#include "StdAfx.h"

extern size_t g_tiles_on_screen_in_x; // at least 6 (border)
extern size_t g_tiles_on_screen_in_y; // at least 4 (border)

extern size_t g_max_map_width ;
extern size_t g_max_map_height;

extern size_t g_max_players;

extern size_t g_bomb_player_has_at_start;
extern size_t g_flame_range_player_has_at_start;

extern double g_bomb_time_to_live;  // (in seconds)

extern bool g_render_aabbs;   // whether or not to render aabbs

#endif
