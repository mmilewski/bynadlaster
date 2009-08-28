#ifndef __PLAYER_CONTROL_H_INCLUDED__
#define __PLAYER_CONTROL_H_INCLUDED__

#include "StdAfx.h"

namespace PA {
  enum PlayerAction {
    None,
    GoRight,
    GoLeft,
    GoUp,
    GoDown,
    GoNowhere,
    
    ActionsCount
  };
}


// Action i is executed for player p by pressing g_player_control[p][i] 
const size_t g_controlled_players_count = 1;
const int g_player_control[g_controlled_players_count][PA::ActionsCount] = { 
  { 0, SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN }, // player 0
};


#endif 
