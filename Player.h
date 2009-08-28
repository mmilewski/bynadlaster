#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "PlayerControl.h"
#include "StdAfx.h"
#include "AABB.h"

class Player {
public:
  explicit Player(Position initial_position);

  void Draw();
  void Update(double dt);
  const Position& GetPosition() const { return m_position; }
  Position GetNextPosition(double dt) const;
  const Direction& GetDirection() const { return m_direction; }
  void PerformAction(PA::PlayerAction action);
  void StopAction(PA::PlayerAction action);
  AABB GetAABB() const;
  AABB GetNextAABB(double dt) const;
  
private:
  Position m_position;
  Direction m_direction;
};

typedef boost::shared_ptr<Player> PlayerPtr;

#endif
