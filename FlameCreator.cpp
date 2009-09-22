#include "Map.h"
#include "Game.h"
#include "FlameCreator.h"
#include "Flame.h"


FlameCreator::FlameCreator(size_t owner_id, Position initial_position, size_t range)
  : m_owner_id(owner_id), m_position(initial_position), m_range(range) {
}


void FlameCreator::Create(Game& game) {
  MapPtr map = game.GetMap();
  const Position pos = m_position;
  double up(0), down(0), left(0), right(0);  // length of flame in four directions
  double length_up(0), length_left(0), length_down(0), length_right(0);

  // determine how long can flame become because of map obstacles
  for (size_t i=1; i<=GetRange(); ++i) {
    if (map->IsFieldStandable(pos.x,pos.y+i))
      length_up++;
    else
      break;
  }
  for (size_t i=1; i<=GetRange(); ++i) {
    if (map->IsFieldStandable(pos.x,pos.y-i))
      length_down++;
    else
      break;
  }
  for (size_t i=1; i<=GetRange(); ++i) {
    if (map->IsFieldStandable(pos.x+i,pos.y))
      length_right++;
    else
      break;
  }
  for (size_t i=1; i<=GetRange(); ++i) {
    if (map->IsFieldStandable(pos.x-i,pos.y))
      length_left++;
    else
      break;
  }

  const double flameWidth = 1.0/g_tiles_on_screen_in_x;
  const double flameHeight = 1.0/g_tiles_on_screen_in_y;
  up = length_up/static_cast<double>(g_tiles_on_screen_in_y);
  down = length_down/static_cast<double>(g_tiles_on_screen_in_y);
  left = length_left/static_cast<double>(g_tiles_on_screen_in_x);
  right = length_right/static_cast<double>(g_tiles_on_screen_in_x);

  game.AddObject(FlamePtr(new Flame(pos+Position(1,0), Size(right,flameHeight), FD::Right)));
  game.AddObject(FlamePtr(new Flame(pos+Position(0,1), Size(flameWidth,up), FD::Up)));
  game.AddObject(FlamePtr(new Flame(pos-Position(length_left,0), Size(left,flameHeight), FD::Left)));
  game.AddObject(FlamePtr(new Flame(pos-Position(0,length_down), Size(flameWidth,down), FD::Down)));
  game.AddObject(FlamePtr(new Flame(pos, Size(flameWidth,flameHeight), FD::Center)));
}
