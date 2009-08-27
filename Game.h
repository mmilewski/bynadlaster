#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "StdAfx.h"



class Game {
public:
  explicit Game();

  void Update(double dt);
  void Draw();
  
  bool IsDone() const { return m_is_done; }
  void Finish() { m_is_done = true; } 

  void HandleInput(const SDL_Event& event);

private:
  bool m_is_done;
  
};


typedef boost::shared_ptr<Game> GamePtr;


#endif
