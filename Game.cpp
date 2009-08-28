#include "Renderer.h"
#include "Bomb.h"
#include "PlayerControl.h"
#include "Game.h"
#include "Map.h"


Game::Game() 
  : m_is_done(false) {
  m_map.reset(new Map(g_max_map_width, g_max_map_height));
  m_hud.reset(new Hud());
  m_players.push_back(PlayerPtr(new Player(Position(8,7))));

  Renderer::Get().LoadTexture("big_dyna.png");

  // UWAGA. rozmiary kafla na ekranie. Jeżeli ekran nie będzie kwadratowy, to kafle również
  // nie będą kwadratowe. Najlepiej byłoby mieć dostęp do parametru ratio (width/height)
  // okna - wtedy wystarczy ustawić np. tile_width=window_ratio/GetWidth()
  Renderer::Get().SetTileSize(Size(1.0/g_tiles_on_screen_in_x, 1.0/g_tiles_on_screen_in_y));

  m_objects.push_back(ObjectPtr(new Bomb(Position(3,1))));
  m_objects.push_back(ObjectPtr(new Bomb(Position(4,3))));
  m_objects.push_back(ObjectPtr(new Bomb(Position(5,6))));
}


void Game::Update(double dt) {
  m_hud->Update(dt);
  m_map->Update(dt);
  std::for_each(m_objects.begin(), m_objects.end(), boost::bind(&Object::Update, _1, dt));

  // ORDER NOTICE: First, check whether player can into move desired direction
  // and if possible then update of his position (for_each below) is always correct
  BOOST_FOREACH( PlayerPtr& player, m_players ) {
    CheckIfPlayerCollidesWithMap(m_map, player, dt);
  }

  std::for_each(m_players.begin(), m_players.end(), boost::bind(&Player::Update, _1, dt));
}


void Game::CheckIfPlayerCollidesWithMap(const MapPtr& map, PlayerPtr& player, double dt) {
  // check collisions with four corners of player sprite
  AABB aabb = player->GetNextAABB(dt);
  Position max = aabb.GetMax();
  Position min = aabb.GetMin();

  if (!map->IsFieldStandable(min)
      || !map->IsFieldStandable(max)
      || !map->IsFieldStandable(Position(max.x, min.y))
      || !map->IsFieldStandable(Position(min.x, max.y)))
    player->PerformAction(PA::GoNowhere);
}


void Game::Draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  m_map->Draw();
  std::for_each(m_objects.begin(), m_objects.end(), boost::bind(&Object::Draw, _1));
  std::for_each(m_players.begin(), m_players.end(), boost::bind(&Player::Draw, _1));
  m_hud->Draw();

  SDL_GL_SwapBuffers();
}


void Game::HandleInput(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    for (size_t p = 0; p < m_players.size(); ++p) {
      for (size_t i = 0; i < PA::ActionsCount; ++i) {
	if (g_player_control[p][i] == event.key.keysym.sym) {
	  m_players.at(p)->PerformAction(PA::PlayerAction(i));
	}
      }
    }
  }
  if (event.type == SDL_KEYUP) {
    for (size_t p = 0; p < m_players.size(); ++p) {
      for (size_t i = 0; i < PA::ActionsCount; ++i) {
	if (g_player_control[p][i] == event.key.keysym.sym) {
	  m_players.at(p)->StopAction(PA::PlayerAction(i));
	}
      }
    }
  }
}
