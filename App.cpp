#include "StdAfx.h"
#include "Engine.h"

#include "Game.h"
#include "Menu.h"
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
  if (!m_game_state) {
    return;
  }

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_VIDEORESIZE) {
      Resize(event.resize.w, event.resize.h);
    }
    else if (event.type == SDL_QUIT) {
      m_game_state->Finish();
    }
    else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      if (!HandleInput(event)) {
	m_game_state->HandleInput(event);
      }
    }
    else if (event.type == SDL_MOUSEMOTION) {
      // ignorujemy mysz
    }
    else {
      std::cerr << "Unknown event\n";
    }
  }
}

void App::Init() {
  Engine::Get();
}

void App::InitGl() {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_TEXTURE_2D);

  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.01); // 0.01 (not 0.5) because we need fade outs
  Resize(m_window_width, m_window_height);
}


void App::Run() {
  CreateWindow(800, 600, 32, false);
  InitGl();
    
  Engine::Get().Renderer()->LoadTexture("big_byna.png");
  // UWAGA. rozmiary kafla na ekranie. Jeżeli ekran nie będzie kwadratowy, to kafle również
  // nie będą kwadratowe. Najlepiej byłoby mieć dostęp do parametru ratio (width/height)
  // okna - wtedy wystarczy ustawić np. tile_width=window_ratio/GetWidth()
  Engine::Get().Renderer()->SetTileSize(Size(1.0/g_tiles_on_screen_in_x, 1.0/g_tiles_on_screen_in_y));

//   m_game_state = GameStatePtr(new Menu());     -- it is better not to watch menu for now
  m_game_state = GameStatePtr(new Game());
  while (true) {

    if (m_game_state->IsDone()) {
      MenuPtr menu = boost::dynamic_pointer_cast<Menu>(m_game_state);
      if (menu) {
	if (menu->GetCurrentOption() == Menu::QUIT_GAME) { break; }
	else if (menu->GetCurrentOption() == Menu::START_GAME) {
	  m_game_state = GameStatePtr(new Game());
	}
      }
      else {
	GamePtr game = boost::dynamic_pointer_cast<Game>(m_game_state);
	if (game) { break; }
      }
    }

    ProcessEvents();
    m_game_state->Update( GetDeltaTime() );
    m_game_state->Draw();
  }
}


double App::GetDeltaTime() {
  // calculate delta time
  static unsigned int oldTime = SDL_GetTicks();
  unsigned int newTime = SDL_GetTicks();
  while(newTime==oldTime)
    newTime = SDL_GetTicks();
  double dt = (newTime - oldTime)/1000.0;
  oldTime = newTime;

  // update window caption - every quarter of a second
  const double captionRefreshInterval = .25;
  static double lastCaptionUpdate = 0;
  lastCaptionUpdate += dt;
  if( lastCaptionUpdate >= captionRefreshInterval ) {
    std::stringstream ss;
    ss << "FPS: " << (dt==0 ? 99999 : 1.0/dt);
    SDL_WM_SetCaption(ss.str().c_str(), 0);
    lastCaptionUpdate = 0;
  }

  return dt;
}


bool App::HandleInput(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
    Engine::Get().Scripts()->Reset();
    return true;
  }
  return false;
}
