#include "Renderer.h"
#include "Game.h"


Game::Game() 
  : m_is_done(false) {
  m_map.reset(new Map(g_max_map_width, g_max_map_height));

  Renderer::Get().LoadTexture("big_dyna.png");
}


void Game::Update(double dt) {
  m_map->Update(dt);  
}


void Game::Draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  m_map->Draw();

  SDL_GL_SwapBuffers();
}


void Game::HandleInput(const SDL_Event& event) {

}

