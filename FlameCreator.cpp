#include "Map.h"
#include "Game.h"
#include "FlameCreator.h"
#include "Flame.h"


FlameCreator::FlameCreator(size_t owner_id, Position initial_position, size_t range)
  : m_owner_id(owner_id), m_position(initial_position), m_range(range) {
}


void FlameCreator::Create(Game& game) {
  MapPtr map = game.GetMap();
  const Position pos = m_position;   // center (left,bottom point) of the fire/flame/blast/whatever
  double length_up(0), length_left(0), length_down(0), length_right(0);  // length of flame in four directions
  const size_t fireRange = GetRange();

  // determine how long can flame become because of map obstacles
  for (size_t i=1; i<=fireRange; ++i) {
    if (map->IsFieldStandable(pos.x,pos.y+i))
      length_up++;
    else
      break;
  }
  for (size_t i=1; i<=fireRange; ++i) {
    if (map->IsFieldStandable(pos.x,pos.y-i))
      length_down++;
    else
      break;
  }
  for (size_t i=1; i<=fireRange; ++i) {
    if (map->IsFieldStandable(pos.x+i,pos.y))
      length_right++;
    else
      break;
  }
  for (size_t i=1; i<=fireRange; ++i) {
    if (map->IsFieldStandable(pos.x-i,pos.y))
      length_left++;
    else
      break;
  }

  /* Computations below u change at your own risk. Be sure u know what is going on here.
     All length_* are computed the same way, so I describe only length_right variable.
     What we want to do is to decrease length_right by a small value, when
     length_right==fireRange - we dont want it to collide with field that is on flame's
     right side, so we make it a bit smaller.

     sizeFactor & positionOffset are used to center flames (including center flame). Why?
     Because then their's aabbs become centered. We *assume* that field's size is (1.0,1.0).
   */

  length_right += (length_right==fireRange) ? -.01 : 0;
  length_left += (length_left==fireRange) ? -.01 : 0;
  length_down += (length_down==fireRange) ? -.01 : 0;
  length_up += (length_up==fireRange) ? -.01 : 0;

  // we need to rescale width & height of flames' lengths
  const double sizeFactor = .99;
  const double positionOffset = (1-sizeFactor)/2.0;
  
  const double flameWidth = (1.0/g_tiles_on_screen_in_x) * sizeFactor;
  const double flameHeight = (1.0/g_tiles_on_screen_in_y) * sizeFactor;
  const double up = length_up/static_cast<double>(g_tiles_on_screen_in_y);
  const double down = length_down/static_cast<double>(g_tiles_on_screen_in_y);
  const double left = length_left/static_cast<double>(g_tiles_on_screen_in_x);
  const double right = length_right/static_cast<double>(g_tiles_on_screen_in_x);

  game.AddObject(FlamePtr(new Flame(pos+Position(1+positionOffset, 0+positionOffset),
                                    Size(right,flameHeight), FD::Right)));         // right arm
  game.AddObject(FlamePtr(new Flame(pos+Position(0+positionOffset, 1+positionOffset),
                                    Size(flameWidth,up), FD::Up)));                // top arm
  game.AddObject(FlamePtr(new Flame(pos-Position(length_left,0-positionOffset),
                                    Size(left,flameHeight), FD::Left)));  // left arm
  game.AddObject(FlamePtr(new Flame(pos-Position(0-positionOffset,length_down),
                                    Size(flameWidth,down), FD::Down)));   // bottom arm
  game.AddObject(FlamePtr(new Flame(pos+Position(positionOffset, positionOffset),
                                    Size(flameWidth,flameHeight), FD::Center)));
}
