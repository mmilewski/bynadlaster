#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "StdAfx.h"
#include "Map.h"
#include "Object.h"
#include "NonEntity.h"
#include "Player.h"
#include "Hud.h"


class Game {
public:
  explicit Game();

  void Update(double dt);
  void Draw();
  
  bool IsDone() const { return m_is_done; }
  void Finish() { m_is_done = true; } 

  bool HandleInput(const SDL_Event& event);

  MapPtr GetMap() { return m_map; }
  void AddObject(ObjectPtr object) { m_objects.push_back(object); }

protected:
  void CheckIfPlayerCollidesWithMap(const MapPtr& map, PlayerPtr& player, double dt);
  bool HandleInputGame(const SDL_Event& event);
  bool HandleInputPlayers(const SDL_Event& event);

private:
  bool m_is_done;
  MapPtr m_map;
  std::vector<ObjectPtr> m_objects;   // enemies, fire, bomb, ups
  std::vector<PlayerPtr> m_players;
  std::vector<NonEntityPtr> m_non_entities; // objects that do not affect the player
  HudPtr m_hud;
};


typedef boost::shared_ptr<Game> GamePtr;


#endif
