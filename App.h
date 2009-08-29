#ifndef __APP_H_INCLUDED__
#define __APP_H_INCLUDED__


#include "StdAfx.h"
#include "Game.h"

class App {
public:
  explicit App() {
    Init();
  }

  void Run();


protected:
  void CreateWindow(int width, int height, int depth, bool fullscreen);
  void Resize(int width, int height);
  void ProcessEvents();
  bool ProcessKey(const SDL_Event& event);
  void InitGl();
  void Init();

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
