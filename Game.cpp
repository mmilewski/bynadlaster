#include "Renderer.h"
#include "Bomb.h"
#include "Game.h"
#include "Map.h"
#include "Creator.h"
#include "Powerup.h"
#include "BombPowerup.h"
#include "FireRangePowerup.h"

#include "PlayerControllers.h"


Game::Game() 
  : m_is_done(false) {
  m_map.reset(new Map(g_max_map_width, g_max_map_height));
  m_hud.reset(new Hud());

  m_players.push_back(PlayerPtr(new Player(0,  // id
					   Position(8,7), 
					   PT::White, 
					   PlayerControllerPtr(new PlayerControllerKb()))));

  Renderer::Get().LoadTexture("big_byna.png");

  // UWAGA. rozmiary kafla na ekranie. Jeżeli ekran nie będzie kwadratowy, to kafle również
  // nie będą kwadratowe. Najlepiej byłoby mieć dostęp do parametru ratio (width/height)
  // okna - wtedy wystarczy ustawić np. tile_width=window_ratio/GetWidth()
  Renderer::Get().SetTileSize(Size(1.0/g_tiles_on_screen_in_x, 1.0/g_tiles_on_screen_in_y));

  const size_t pid = m_players.at(0)->GetId();
  const size_t range = m_players.at(0)->GetFireRange();
  m_objects.push_back(ObjectPtr(new Bomb(pid,Position(3,1),range)));
  m_objects.push_back(ObjectPtr(new Bomb(pid,Position(4,3),range)));
  m_objects.push_back(ObjectPtr(new Bomb(pid,Position(5,6),range)));
  m_objects.push_back(ObjectPtr(new BombPowerup(Position(4,6))));
  m_objects.push_back(ObjectPtr(new BombPowerup(Position(3,8))));
  m_objects.push_back(ObjectPtr(new FireRangePowerup(Position(5,3))));
  m_objects.push_back(ObjectPtr(new FireRangePowerup(Position(3,5))));
}


void Game::Update(double dt) {
  m_hud->Update(dt);
  m_map->Update(dt);

  std::for_each(m_objects.begin(), m_objects.end(), boost::bind(&Object::Update, _1, dt));

  BOOST_FOREACH(PlayerPtr& player, m_players) {
    CheckIfPlayerCollidesWithMap(m_map, player, dt);
  }

  BOOST_FOREACH(PlayerPtr& player, m_players) {
    BOOST_FOREACH(ObjectPtr& object, m_objects) {
      if(!object->IsAlive())      // object should be swept, not processed
        continue;
      switch(object->GetType()) {
      case OT::Bomb:
        if(player->GetNextAABB(dt).IntersectsUsingDirectionWith(object->GetAABB(), player->GetDirection())) {
          player->PerformAction(PA::GoNowhere);
        }
        break;
//       case OT::Fire:
//         player->Burnt();
//         break;
//       case OT::Enemy:
//         player->KilledByEnemy();
//         break;
      case OT::Powerup:
        if(player->GetAABB().CollidesWith(object->GetAABB())) {
          player->GivePowerup(boost::dynamic_pointer_cast<Powerup>(object));
          object->SetAliveFlag(false);
        }
        break;
      default:
        std::cerr << "collision player<->" << object->GetType() << " unsupported\n";
      }
    }
  }

  DataForController data_for_controller;
  std::for_each(m_players.begin(), m_players.end(), boost::bind(&Player::Update, _1, data_for_controller, dt));

//   std::cout << "#bombs = " << m_players.at(0)->GetBombCount() << "  "
//             << "fireRange = " << m_players.at(0)->GetFireRange() << "\n";

  m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), !boost::bind(&Object::IsAlive,_1)),
                  m_objects.end());

  // collect creators from objects && players together and run them all
  std::list<CreatorPtr> all_creators;
  BOOST_FOREACH( ObjectPtr obj, m_objects ) {
    std::list<CreatorPtr>& obj_creators = obj->GetAllCreators();
    all_creators.splice(all_creators.end(), obj_creators);
  }
  BOOST_FOREACH( PlayerPtr plr, m_players ) {
    std::list<CreatorPtr>& plr_creators = plr->GetAllCreators();
    all_creators.splice(all_creators.end(), plr_creators);
  }
  BOOST_FOREACH( CreatorPtr creator, all_creators ) {
    creator->Create(*this);
  }
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


bool Game::HandleInput(const SDL_Event& event) {
  if (HandleInputGame(event)) return true;
  if (HandleInputPlayers(event)) return true;
  return false;
}


bool Game::HandleInputGame(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_1) {
      m_players.at(0)->SetType(PT::White);
      return true;
    }
    else if (event.key.keysym.sym == SDLK_2) {
      m_players.at(0)->SetType(PT::Green);
      return true;
    }
    else if (event.key.keysym.sym == SDLK_3) {
      m_players.at(0)->SetType(PT::Red);
      return true;
    }
    else if (event.key.keysym.sym == SDLK_4) {
      m_players.at(0)->SetType( PT::Blue);
      return true;
    }
    else if (event.key.keysym.sym == SDLK_RETURN) {
      m_players.at(0)->SetDie(!m_players.at(0)->IsDying());
      return true;
    }
  }
  return false;
}


bool Game::HandleInputPlayers(const SDL_Event& event) {
  for (size_t player_id = 0; player_id < m_players.size(); ++player_id) {
    if (m_players.at(player_id)->HandleInput(event)) {
     return true;
    }      
  }
  return false;
}
