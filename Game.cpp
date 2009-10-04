#include "Engine.h"
#include "Bomb.h"
#include "Game.h"
#include "Map.h"
#include "Creator.h"
#include "Powerup.h"
#include "BombPowerup.h"
#include "Flame.h"
#include "FlameRangePowerup.h"

#include "PlayerControllers.h"

#include "Text.h"
#include "AfterKillPoints.h"

#include "BoxInFire.h"


Game::Game() {
  m_map.reset(new Map(g_max_map_width, g_max_map_height));
  m_hud.reset(new Hud());

  m_players.push_back(PlayerPtr(new Player(0,  // id
					   Position(6,8), 
					   PT::White, 
					   PlayerControllerPtr(new PlayerControllerKb()))));

  PlayerPtr owner = m_players.at(0);
  const size_t range = m_players.at(0)->GetFlameRange();

  owner->PlaceBomb(Position(3,1),range);
  owner->PlaceBomb(Position(7,10),range);
  owner->PlaceBomb(Position(19,6),range);
  m_objects.push_back(ObjectPtr(new BombPowerup(Position(4,6))));
  m_objects.push_back(ObjectPtr(new BombPowerup(Position(3,8))));
  m_objects.push_back(ObjectPtr(new FlameRangePowerup(Position(5,3))));
  m_objects.push_back(ObjectPtr(new FlameRangePowerup(Position(3,5))));
}


void Game::DoUpdate(double dt) {
  m_hud->Update(dt);
  m_map->Update(dt);

  std::for_each(m_objects.begin(), m_objects.end(), boost::bind(&Object::Update, _1, dt));

  BOOST_FOREACH(PlayerPtr& player, m_players) {
    CheckIfPlayerCollidesWithMap(m_map, player, dt);
  }

  BOOST_FOREACH(ObjectPtr& object, m_objects) {
    CheckIfObjectCollidesWithMap(m_map, object, dt);
  }

  BOOST_FOREACH(PlayerPtr& player, m_players) {
    BOOST_FOREACH(ObjectPtr& object, m_objects) {
      if(!object->IsAlive())      // object should be swept, not processed
        continue;
      switch(object->GetType()) {
      case OT::Bomb:
        // if player doesn't collide with bomb now && will collide if he moves, then stop him!
        if (player->GetAABB().CollidesWith(object->GetAABB())==false
            && (player->GetNextAABB(dt).IntersectsUsingDirectionWith(object->GetAABB(), player->GetDirection()))) {
          player->PerformAction(PA::GoNowhere);
        }
        break;
      case OT::Flame:
        player->Burnt();
        break;
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

  // check collisions object-object - time complexity O(n^2)
  std::vector<ObjectPtr>::iterator outer = m_objects.begin(), inner;
  for( ; outer!=m_objects.end(); ++outer ) {
    if (false==(*outer)->IsAlive())
      continue;
    inner = outer;
    OT::ObjectType outerType = (*outer)->GetType();
    while (++inner!=m_objects.end()) {
      if ((*inner)->IsAlive() && (*outer)->GetAABB().CollidesWith((*inner)->GetAABB())) {   // is alive && collides
        OT::ObjectType innerType = (*inner)->GetType();
        // bomb <-> flame
        {
          if (innerType==OT::Bomb && outerType==OT::Flame) {
            boost::dynamic_pointer_cast<Bomb>(*inner)->Detonate();
          }
          else if (innerType==OT::Flame && outerType==OT::Bomb) {
            boost::dynamic_pointer_cast<Bomb>(*outer)->Detonate();
          }
        }
      }
    }
  }

  DataForController data_for_controller;
  std::for_each(m_players.begin(), m_players.end(), boost::bind(&Player::Update, _1, data_for_controller, dt));
  std::for_each(m_non_entities.begin(), m_non_entities.end(), boost::bind(&NonEntity::Update, _1, dt));

  //   std::cout << "#bombs = " << m_players.at(0)->GetBombCount() << "  "
  //             << "fireRange = " << m_players.at(0)->GetFireRange() << "\n";

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

  // remove dead objects
  // NOTICE: this should happen after collection creators - else some object may not be created (bomb->flame)
  m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), !boost::bind(&Object::IsAlive,_1)),
                  m_objects.end());

  m_non_entities.erase(std::remove_if(m_non_entities.begin(), m_non_entities.end(), 
				      !boost::bind(&NonEntity::IsAlive,_1)),
		       m_non_entities.end());
}


void Game::CheckIfPlayerCollidesWithMap(const MapPtr& map, PlayerPtr& player, double dt) {
  // check collisions with four corners of player sprite
  const AABB player_aabb = player->GetNextAABB(dt);
  const Position max = player_aabb.GetMax();
  const Position min = player_aabb.GetMin();

  if (!map->IsFieldStandable(min)
      || !map->IsFieldStandable(max)
      || !map->IsFieldStandable(Position(max.x, min.y))
      || !map->IsFieldStandable(Position(min.x, max.y)))
    player->PerformAction(PA::GoNowhere);
}


void Game::CheckIfObjectCollidesWithMap(const MapPtr& map, ObjectPtr& object, double dt) {
  if (object->GetType()!=OT::Flame)
    return;
  FlamePtr flame = boost::dynamic_pointer_cast<Flame>(object);
  const AABB flame_aabb = flame->GetAABB();
  for (size_t y=0; y < map->GetHeight(); ++y) {
    for (size_t x=0; x < map->GetWidth(); ++x) {
      const AABB field_aabb = map->GetFieldAABB(x,y);
      if (map->GetFieldType(x, y)==FT::Box && field_aabb.CollidesWith(flame_aabb)) {  // field is box && aabbs collide
//         std::cout << "Field AABB: " << field_aabb.GetMin() << " " << field_aabb.GetMax() << "\n"
//                   << "Flame AABB: " << flame_aabb.GetMin() << " " << flame_aabb.GetMax() << "\n";
        map->SetFieldType(x, y, FT::Floor);
        m_non_entities.push_back(NonEntityPtr(new BoxInFire(map->GetFieldPosition(x,y))));
      }
    }
  }
#warning TODO: add burning box
}


void Game::DoDraw() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  m_map->Draw();
  std::for_each(m_objects.begin(), m_objects.end(), boost::bind(&Object::Draw, _1));
  std::for_each(m_players.begin(), m_players.end(), boost::bind(&Player::Draw, _1));
  std::for_each(m_non_entities.begin(), m_non_entities.end(), boost::bind(&NonEntity::Draw, _1));
  m_hud->Draw();

  Engine::Get().Renderer()->SwapBuffers();
}


bool Game::DoHandleInput(const SDL_Event& event) {
  if (HandleInputGame(event)) return true;
  if (HandleInputPlayers(event)) return true;
  return false;
}


bool Game::HandleInputGame(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_q) {
      Finish();
      return true;
    }
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
    else if (event.key.keysym.sym == SDLK_RCTRL) {
      m_non_entities.push_back(NonEntityPtr(new AfterKillPoints(Position(0.5, 0.8), AfterKillPoints::Amount(rand()%8))));
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
