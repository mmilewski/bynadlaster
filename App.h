#ifndef __APP_H_INCLUDED__
#define __APP_H_INCLUDED__

#include "StdAfx.h"
#include "GameState.h"

class App {
public:
  explicit App() {
    Init();
  }

  void Run();


protected:
  void CreateWindow(size_t width, size_t height, size_t depth, bool fullscreen);
  void Resize(size_t width, size_t height);
  void ProcessEvents();
  bool HandleInput(const SDL_Event& event);
  void InitGl();
  void Init();

protected:
  /**
   * Zwraca czas (w sekundach) jaki minął od ostatniego wywołania tej metody
   */
  double GetDeltaTime();

private:
  void setupSdlVideo();

private:
  GameStatePtr m_game_state;
  size_t m_window_width;
  size_t m_window_height;
  size_t m_window_depth;
  size_t m_window_flags;
  bool m_window_fullscreen;
  SDL_Surface* m_screen;
};


#endif
