#ifndef __GAME_STATE_H_INCLUDED__
#define __GAME_STATE_H_INCLUDED__

#include "StdAfx.h"

class GameState {
public:
  virtual ~GameState() { }
  explicit GameState() : m_is_done(false) { }

  void Draw() const { DoDraw(); }
  void Update(double dt) { DoUpdate(dt); }

  bool IsDone() const { return m_is_done; }
  void Finish() { m_is_done = true; } 

  bool HandleInput(const SDL_Event& event) { return DoHandleInput(event); }

protected:
  virtual void DoDraw() const = 0;
  virtual void DoUpdate(double dt) = 0;
  virtual bool DoHandleInput(const SDL_Event& event) = 0;


private:
  bool m_is_done;
};

typedef boost::shared_ptr<GameState> GameStatePtr;


#endif
