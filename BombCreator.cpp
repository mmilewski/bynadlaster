#include "Game.h"
#include "Bomb.h"
#include "BombCreator.h"


BombCreator::BombCreator(size_t owner_id, Position initial_position, size_t range)
  : m_owner_id(owner_id), m_position(initial_position), m_range(range) {
}


void BombCreator::Create(Game& game) {
  MapPtr map = game.GetMap();
  Position dst_pos = GetPosition();

#warning check whether it is possible to place a bomb - if there is no other bomb already placed nearby

  if(map->IsFieldStandable(dst_pos))
    game.AddObject(BombPtr(new Bomb(m_owner_id, dst_pos, m_range)));
}
