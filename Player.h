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

  // methods mainly for collision handling
  void IncreaseBombCount()  { m_all_bomb_count++; }
  size_t GetBombCount()  { return m_all_bomb_count; }
  void IncreaseFireRange()  { m_fire_range++; }
  size_t GetFireRange()  { return m_fire_range; }
  void GivePowerup(PowerupPtr powerup);
//   void KilledByEnemy();
//   void Burnt();

  bool HandleInput(const SDL_Event& event);

  // getters
  const Position& GetPosition() const { return m_position; }
  Position GetNextPosition(double dt) const;
  const Direction& GetDirection() const { return m_direction; }

  AABB GetAABB() const;
  AABB GetNextAABB(double dt) const;

  size_t GetId() const { return m_id; }

  PT::PlayerType GetType() const { return m_type; }
  void SetType(PT::PlayerType new_type) { m_type = new_type; }
  
  bool IsDying() const { return m_is_dying; }
  void Die() { SetDie(true); }
  void SetDie(bool die) { m_is_dying = die; }

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

  size_t m_all_bomb_count;     // number of bomb that player can use at all (at all, NOT now)
  size_t m_fire_range;         // how meny fields player's bomb's fire covers

  PlayerControllerPtr m_controller; // chooses action for player to perform
};

typedef boost::shared_ptr<Player> PlayerPtr;

#endif
