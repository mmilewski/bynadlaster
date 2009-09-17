#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "StdAfx.h"
#include "GameState.h"

class Menu : public GameState {
public:
  enum Option {
    START_GAME,
    QUIT_GAME,
    
    OPTIONS_COUNT
  };

public:
  explicit Menu();

  void DoDraw() const;
  void DoUpdate(double dt);
  bool DoHandleInput(const SDL_Event& event);

  Option GetCurrentOption() const { return m_current_option; }

private:
  double m_camera_y;
  Option m_current_option;
};


typedef boost::shared_ptr<Menu> MenuPtr;

#endif
