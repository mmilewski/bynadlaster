#ifndef __PLAYER_CONTROLLER_KB_H__
#define __PLAYER_CONTROLLER_KB_H__

#include "PlayerController.h"


class PlayerControllerKb : public PlayerController {
protected:
  void DoUpdate(const DataForController& data, double dt) const { 

  }

  bool DoHandleInput(const SDL_Event& event) { 
    if (event.type == SDL_KEYDOWN) {
      for (size_t i = 0; i < PA::ActionsCount; ++i) {
	if (g_player_control[GetPlayerId()][i] == event.key.keysym.sym) {
	  SetNextAction(PA::PlayerAction(i));
	  return true;
	}
      }
    }

    if (event.type == SDL_KEYUP) {
      for (size_t i = 0; i < PA::ActionsCount; ++i) {
	if (g_player_control[GetPlayerId()][i] == event.key.keysym.sym) {
	  SetNextAction(PA::PlayerAction(i + PA::FirstStopAction));
	  return true;
	}
      }
    }

    return false; 
  }
};


#endif
