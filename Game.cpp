#include "Renderer.h"
#include "Game.h"
#include "Bomb.h"


Game::Game() 
  : m_is_done(false) {
  m_map.reset(new Map(g_max_map_width, g_max_map_height));

  Renderer::Get().LoadTexture("big_dyna.png");

  // UWAGA. rozmiary kafla na ekranie. Jeżeli ekran nie będzie kwadratowy, to kafle również
  // nie będą kwadratowe. Najlepiej byłoby mieć dostęp do parametru ratio (width/height)
  // okna - wtedy wystarczy ustawić np. tile_width=window_ratio/GetWidth()
  Renderer::Get().SetTileSize(1.0/m_map->GetWidth(), 1.0/m_map->GetHeight());


  m_objects.push_back(ObjectPtr(new Bomb(Position(3,3))));
  m_objects.push_back(ObjectPtr(new Bomb(Position(1,2))));
}


void Game::Update(double dt) {
  m_map->Update(dt);  
}


void Game::Draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  m_map->Draw();
  std::for_each(m_objects.begin(), m_objects.end(), boost::bind(&Object::Draw, _1));

  SDL_GL_SwapBuffers();
}


void Game::HandleInput(const SDL_Event& event) {

}

