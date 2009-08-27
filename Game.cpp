#include "Renderer.h"
#include "Game.h"


Game::Game() 
  : m_is_done(false) {
  
}


void Game::Update(double dt) {
  
}


void Game::Draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  Renderer::Get().LoadTexture("big_dyna.png");
  Renderer::Get().DrawSprite(Position(0, 0, .5, .5), TexCoords(0, 0, .1, .1));  

  SDL_GL_SwapBuffers();
}


void Game::HandleInput(const SDL_Event& event) {

}

