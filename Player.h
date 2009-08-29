#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "PlayerControl.h"
#include "StdAfx.h"
#include "AABB.h"
#include "Powerup.h"


class Player {
public:
  explicit Player(Position initial_position);

  void Draw();
  void Update(double dt);
  void PerformAction(PA::PlayerAction action);
  void StopAction(PA::PlayerAction action);

  // methods mainly for collision handling
  void IncreaseBombCount()  { m_all_bomb_count++; }
  size_t GetBombCount()  { return m_all_bomb_count; }
  void IncreaseFireRange()  { m_fire_range++; }
  size_t GetFireRange()  { return m_fire_range; }
  void GivePowerup(PowerupPtr powerup);
//   void KilledByEnemy();
//   void Burnt();

  // getters
  const Position& GetPosition() const { return m_position; }
  Position GetNextPosition(double dt) const;
  const Direction& GetDirection() const { return m_direction; }
  AABB GetAABB() const;
  AABB GetNextAABB(double dt) const;

private:
  Position m_position;
  Direction m_direction;
  size_t m_all_bomb_count;     // number of bomb that player can use at all (at all, NOT now)
  size_t m_fire_range;         // how meny fields player's bomb's fire covers
};

typedef boost::shared_ptr<Player> PlayerPtr;

#endif
