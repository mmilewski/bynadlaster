#include "Game.h"
#include "Bomb.h"
#include "BombCreator.h"


BombCreator::BombCreator(Position initial_position)
  : m_position(initial_position) {
}


void BombCreator::Create(Game& game) {
  MapPtr map = game.GetMap();
  Position dst_pos = GetPosition();
  if(map->IsFieldStandable(dst_pos))
    game.AddObject(BombPtr(new Bomb(dst_pos)));
}
