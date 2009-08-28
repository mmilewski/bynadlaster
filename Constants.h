#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

const unsigned int g_tiles_on_screen_in_x = 23; // at least 6 (border)
const unsigned int g_tiles_on_screen_in_y = 23; // at least 4 (border)

const unsigned int g_max_map_width  = g_tiles_on_screen_in_x - 6;
const unsigned int g_max_map_height = g_tiles_on_screen_in_y - 4;

const unsigned int g_max_players = 2;

#endif
