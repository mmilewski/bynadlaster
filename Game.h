#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

#include "StdAfx.h"
#include "Map.h"
#include "Object.h"
#include "NonEntity.h"
#include "Player.h"
#include "Hud.h"
#include "GameState.h"

class Game : public GameState {
public:
  explicit Game();

  MapPtr GetMap() { return m_map; }
  void AddObject(ObjectPtr object) { m_objects.push_back(object); }

  const std::vector<ObjectPtr>& GetObjects()  { return m_objects; }
//   const std::vector<PlayerPtr>& GetPlayers()  { return m_players; }
  PlayerPtr GetPlayerById(size_t id)  { return *(find_if(m_players.begin(), m_players.end(), boost::bind(&Player::GetId,_1)==id)); }

protected:
  void CheckIfPlayerCollidesWithMap(const MapPtr& map, PlayerPtr& player, double dt);
  void CheckIfObjectCollidesWithMap(const MapPtr& map, ObjectPtr& object, double dt);
  bool HandleInputGame(const SDL_Event& event);
  bool HandleInputPlayers(const SDL_Event& event);

protected:
  void DoDraw() const;
  void DoUpdate(double dt);
  bool DoHandleInput(const SDL_Event& event);

private:
  MapPtr m_map;
  std::vector<ObjectPtr> m_objects;   // enemies, fire, bomb, ups
  std::vector<PlayerPtr> m_players;
  std::vector<NonEntityPtr> m_non_entities; // objects that do not affect the player
  HudPtr m_hud;
};


typedef boost::shared_ptr<Game> GamePtr;


#endif
