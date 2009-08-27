#include "App.h"


void App::CreateWindow(int width, int height, int depth, bool fullscreen) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Unable to initialize Window Manager (SDL)" << std::flush;
    exit(1);
  }

  SDL_Surface* screen = SDL_SetVideoMode(width, height, depth, 
					 SDL_HWSURFACE 
					 | SDL_OPENGL
					 | SDL_RESIZABLE
					 | (fullscreen ? SDL_FULLSCREEN : 0));
  if (!screen) {
    std::cerr << "Unable to create OpenGL context (SDL)" << std::flush;
    exit(1);
  }
    
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  m_window_width = width;
  m_window_height = height;
}


void App::Resize(int width, int height) {
  glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void App::ProcessEvents() {
  if (!m_game) {
    return;
  }

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_VIDEORESIZE) {
      Resize(event.resize.w, event.resize.h);
    }
    else if (event.type == SDL_QUIT) {
      m_game->Finish();
    }
    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      m_game->HandleInput(event);
    }
    else if (event.type == SDL_MOUSEMOTION) {
      // ignorujemy mysz
    }
    else {
      std::cerr << "Unknown event\n";
    }
  }
}


void App::InitGl() {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  Resize( m_window_width, m_window_height );
}


void App::Run() {
  CreateWindow(600, 600, 32, false);
  InitGl();
    
  m_game.reset(new Game());
  while (!m_game->IsDone()) {
    ProcessEvents();
    m_game->Update( GetDeltaTime() );
    m_game->Draw();
  }
}


double App::GetDeltaTime() {
  // wylicz dt
  static unsigned int oldTime = SDL_GetTicks();
  unsigned int newTime = SDL_GetTicks();
  while(newTime==oldTime)
    newTime = SDL_GetTicks();
  double dt = (newTime - oldTime)/1000.0;
  oldTime = newTime;

  // update belki okna - co sekundę
  const double captionRefreshInterval = .25;
  static double lastCaptionUpdate = 0;
  lastCaptionUpdate += dt;
  if( lastCaptionUpdate > captionRefreshInterval ) {
    std::stringstream ss;
    ss << "FPS: " << 1.0/dt;
    SDL_WM_SetCaption( ss.str().c_str(), 0 );
    lastCaptionUpdate = 0;
  }

  return dt;
}
