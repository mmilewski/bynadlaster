#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "PlayerAction.h"
#include "StdAfx.h"
#include "AABB.h"
#include "Powerup.h"
#include "PlayerController.h"


class Player {
public:
  explicit Player(size_t id, Position initial_position, PT::PlayerType type, PlayerControllerPtr controller);

  void Draw();
  void Update(const DataForController& data, double dt);
  void PerformAction(PA::PlayerAction action);
  void StopAction(PA::PlayerAction action);

  void IncreaseBombCount()  { m_all_bomb_count++; }
  size_t GetAllBombCount()  { return m_all_bomb_count; }
  size_t GetUsedBombCount()  { return m_used_bomb_count; }
  void IncreaseUsedBombCount()  { m_used_bomb_count++; }
  void DecreaseUsedBombCount()  { m_used_bomb_count--; }
  size_t GetAvailableBombCount()  { return GetAllBombCount() - GetUsedBombCount(); }
  void IncreaseFlameRange()  { m_flame_range++; }
  size_t GetFlameRange()  { return m_flame_range; }
  void GivePowerup(PowerupPtr powerup);
  // methods mainly for collision handling
//   void KilledByEnemy();
  void Burnt();

  bool HandleInput(const SDL_Event& event);

  // getters
  const Position& GetPosition() const { return m_position; }
  Position GetCenterPosition() const { return GetPosition() + Position(.5,.5); }
  Position GetNextPosition(double dt) const;
  Position GetNextCenterPosition(double dt) const { return GetNextPosition(dt) + Position(.5,.5); }
  const Direction& GetDirection() const { return m_direction; }

  AABB GetAABB() const;
  AABB GetNextAABB(double dt) const;

  size_t GetId() const { return m_id; }

  PT::PlayerType GetType() const { return m_type; }
  void SetType(PT::PlayerType new_type) { m_type = new_type; }
  
  bool IsDying() const { return m_is_dying; }
  void Die() { SetDie(true); }
  void SetDie(bool die) { m_is_dying = die; }

  /** Sets bomb at player's position and with player's flame range */
  void PlaceBomb();

  /** Sets bomb at custom position and with custom flame range */
  void PlaceBomb(const Position& position, size_t range);

  std::list<CreatorPtr>& GetAllCreators()  { return m_creators; }

protected:
  void AddCreator(CreatorPtr creator)  { m_creators.insert(m_creators.end(), creator); }

  PlayerControllerPtr GetController() const { return m_controller; }
  void SetController(PlayerControllerPtr new_controller) { 
    m_controller = new_controller;
    m_controller->SetPlayerId(GetId());
  }

private:
  size_t m_id; // index in players vector (in game)

  std::list<CreatorPtr> m_creators;

  Position m_position;
  Direction m_direction;

  PT::PlayerType m_type; 

  size_t m_current_action_start_time;
  bool   m_is_dying;

  size_t m_all_bomb_count;     // number of bombs that player can use at all (at all, NOT now)
  size_t m_used_bomb_count;    // number of bombs in use (placed but not detonated yet)
  size_t m_flame_range;         // how meny fields player's bomb's flame covers

  PlayerControllerPtr m_controller; // chooses action for player to perform
};

typedef boost::shared_ptr<Player> PlayerPtr;

#endif
