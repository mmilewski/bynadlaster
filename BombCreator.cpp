#include "Game.h"
#include "Bomb.h"
#include "BombCreator.h"


BombCreator::BombCreator(size_t owner_id, Position initial_position, size_t range)
  : m_owner_id(owner_id), m_position(initial_position), m_range(range) {
}


void BombCreator::Create(Game& game) {
  MapPtr map = game.GetMap();
  const Position bomb_dst_pos = Position(floor(GetPosition().x+.5), floor(GetPosition().y+.5));
  PlayerPtr bomb_owner = game.GetPlayerById(m_owner_id);
  BombPtr bomb = BombPtr(new Bomb(bomb_owner, bomb_dst_pos, m_range));
  const AABB bomb_aabb = bomb->GetAABB();
  bool can_place_bomb = true;

  const std::vector<ObjectPtr>& gameObjects = game.GetObjects();
  //   const std::vector<PlayerPtr>& gplayers = game.GetPlayers();
  BOOST_FOREACH(ObjectPtr obj, gameObjects) {
    if (obj->GetAABB().CollidesWith(bomb_aabb)) {
      can_place_bomb = false;
      break;
    }
  }

  if (can_place_bomb && map->IsFieldStandable(bomb_dst_pos)) {
    bomb_owner->IncreaseUsedBombCount();
    game.AddObject(bomb);
  }
}
