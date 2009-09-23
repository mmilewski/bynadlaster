#include "Constants.h"

// (!) WARNING (!)
//
// You should not modify this file. This values are never used (should
// be). All settings are overwritten by Config class (values are
// loaded from lua code scripts/main_config.lua)


size_t g_tiles_on_screen_in_x = 23; // at least 6 (border)
size_t g_tiles_on_screen_in_y = 23; // at least 4 (border)

size_t g_max_map_width = g_tiles_on_screen_in_x - 6;
size_t g_max_map_height = g_tiles_on_screen_in_y;

size_t g_max_players = 2;

size_t g_bomb_player_has_at_start = 3;
size_t g_fire_range_player_has_at_start = 2;

double g_bomb_time_to_live = 3.0;  // (in seconds)

bool g_render_aabbs = true;
