#include "Map.h"
#include "Game.h"
#include "FlameCreator.h"


FlameCreator::FlameCreator(size_t owner_id, Position initial_position, size_t range)
  : m_owner_id(owner_id), m_position(initial_position), m_range(range) {
}


void FlameCreator::AddFlame(double xpos, double ypos) {
#warning implement AddFlame. Remember about owner_id
}


void FlameCreator::Create(Game& game) {
  MapPtr map = game.GetMap();
  Position pos = map->PositionToPositionOnMap(m_position);
  size_t up(0), down(0), left(0), right(0);  // length of flame in four directions

  // add flames in each of four directions. Add a lot of small, collidable flames objects
  // and a not collidable FireRepresentations object (flame that players can see in game).

#warning implement creating flame
//   for (size_t i=0; i<m_range; ++i) {
//     if (map->IsFieldStandable(pos.x, pos.y+i)) {
//       ++up;
//       AddFlame(pos.x, pos.y+i);
//       AddFlame(pos.x, pos.y+i+.5);
//     }
//   }

//   for (size_t i=0; i<m_range; ++i) {
//     if (map->IsFieldStandable(pos.x, pos.y-i)) {
//       ++down;
//       AddFlame(pos.x, pos.y-i);
//       AddFlame(pos.x, pos.y-i-.5);
//     }
//   }

//   for (size_t i=0; i<m_range; ++i) {
//     if (map->IsFieldStandable(pos.x+i, pos.y)) {
//       ++right;
//       AddFlame(pos.x+i, pos.y);
//       AddFlame(pos.x+i+.5, pos.y);
//     }
//   }

//   for (size_t i=0; i<m_range; ++i) {
//     if (map->IsFieldStandable(pos.x-i, pos.y)) {
//       ++left;
//       AddFlame(pos.x-i, pos.y);
//       AddFlame(pos.x-i-.5, pos.y);
//     }
//   }

#warning implement creating FireRepresentation
//   game.AddObject(ObjectPtr(new FireRepresentation(up, left, down, right)));

}
