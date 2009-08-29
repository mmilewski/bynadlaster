#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

const size_t g_tiles_on_screen_in_x = 23; // at least 6 (border)
const size_t g_tiles_on_screen_in_y = 23; // at least 4 (border)

const size_t g_max_map_width  = g_tiles_on_screen_in_x - 6;
const size_t g_max_map_height = g_tiles_on_screen_in_y - 4;

const size_t g_max_players = 2;

const size_t g_bomb_player_has_at_start = 3;
const size_t g_fire_range_player_has_at_start = 2;

#endif
