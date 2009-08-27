#ifndef __APP_H_INCLUDED__
#define __APP_H_INCLUDED__


#include "StdAfx.h"
#include "Game.h"

class App {
public:
  void CreateWindow(int width, int height, int depth, bool fullscreen);
  void Resize(int width, int height);
  void ProcessEvents();
  void InitGl();
  void Run();

  GamePtr m_game;
};


#endif
