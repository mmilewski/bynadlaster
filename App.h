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

protected:
  /**
   * Zwraca czas (w sekundach) jaki minął od ostatniego wywołania tej metody
   */
  double GetDeltaTime();

private:
  GamePtr m_game;
  int m_window_width;
  int m_window_height;
};


#endif
