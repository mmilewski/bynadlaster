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
      std::cerr << "Uknown event\n";
    }
  }
}


void App::InitGl() {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);
}


void App::Run() {
  CreateWindow(800, 600, 32, false);
  InitGl();
    
  m_game.reset(new Game());
  while (!m_game->IsDone()) {
    ProcessEvents();
#warning Plicz DT
    m_game->Update(0);
    m_game->Draw();
  }
}
