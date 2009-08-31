#ifndef __PLAYER_CONTROL_H_INCLUDED__
#define __PLAYER_CONTROL_H_INCLUDED__

#include "StdAfx.h"


//  (!) WARNING (!)
// Don't even try to move this to Types.h.  It must be here because
// the order of values is important (must be the same as int
// g_player_control)
struct PA {
  // (!) NOTE (1)
  enum PlayerAction {
    None,

    GoRight,
    GoLeft,
    GoUp,
    GoDown,
    PlaceBomb,

    GoNowhere,
    
    FirstStopAction,
    StopGoRight,
    StopGoLeft,
    StopGoUp,
    StopGoDown,

    ActionsCount
  };


  static void RegisterInLua(lua_State* lua_state) {
    luabind::module(lua_state) [
				luabind::class_<PA>("PA")
				// (!) NOTE (1)
				.enum_("FieldType") [
						     luabind::value("None"     , PA::None),
						     luabind::value("GoRight"  , PA::GoRight),
						     luabind::value("GoLeft"   , PA::GoLeft),
						     luabind::value("GoUp"     , PA::GoUp),
						     luabind::value("GoDown"   , PA::GoDown),
						     luabind::value("GoNowhere", PA::GoNowhere),
						     luabind::value("PlaceBomb", PA::GoNowhere),

						     luabind::value("FirstStopAction", PA::FirstStopAction),
						     luabind::value("StopGoRight"    , PA::StopGoRight),
						     luabind::value("StopGoLeft"     , PA::StopGoLeft),
						     luabind::value("StopGoUp"       , PA::StopGoUp),
						     luabind::value("StopGoDown"     , PA::StopGoDown),

						     luabind::value("ActionsCount", PA::ActionsCount)
						     ]
				];
  }

};


// Action i is executed for player p by pressing g_player_control[p][i] 
const size_t g_controlled_players_count = 1;
const int g_player_control[g_controlled_players_count][PA::ActionsCount] = { 
  { 0, SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN, SDLK_o }, // player 0
};


#endif 
