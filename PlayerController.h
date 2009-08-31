#ifndef __PLAYER_CONTROLLER_H_INCLUDED__
#define __PLAYER_CONTROLLER_H_INCLUDED__

#include "StdAfx.h" 
#include "DataForController.h"


class PlayerController {
public:
  explicit PlayerController() : m_player_id(0), m_next_action(PA::None) { }
  virtual ~PlayerController() { }

  void Update(const DataForController& data, double dt) { DoUpdate(data, dt); }
  bool HandleInput(const SDL_Event& event) { return DoHandleInput(event); }
  PA::PlayerAction GetNextAction() { return m_next_action; }

  void SetPlayerId(size_t player_id) { m_player_id = player_id; }
  size_t GetPlayerId() const { return m_player_id; }

  void ResetNextAction() { SetNextAction(PA::None); }

protected:
  void SetNextAction(PA::PlayerAction next_action) { m_next_action = next_action; }

protected:
  virtual void DoUpdate(const DataForController& data, double dt) const = 0;
  virtual bool DoHandleInput(const SDL_Event& event) = 0;

private:
  size_t m_player_id;
  PA::PlayerAction m_next_action;

};

typedef boost::shared_ptr<PlayerController> PlayerControllerPtr;


#endif
