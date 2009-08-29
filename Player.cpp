#include "Renderer.h"
#include "Player.h"


Player::Player(Position initial_position, PT::PlayerType type) 
  : m_position(initial_position),
    m_direction(0,0),
    m_type(type),
    m_current_action_start_time(SDL_GetTicks()),
    m_is_dying(false),
    m_all_bomb_count(g_bomb_player_has_at_start),
    m_fire_range(g_fire_range_player_has_at_start) {
}


void Player::Draw() {
  Renderer::Get().DrawSprite(m_position, Lua::Get().GetPlayerSprite(GetType(), 
								    GetDirection(), 
								    IsDying(), 
								    SDL_GetTicks() - m_current_action_start_time)
			     );
}


void Player::Update(double dt) {
  m_position = GetNextPosition(dt);
}


void Player::GivePowerup(PowerupPtr powerup) {
  powerup->Affect(*this);
}


Position Player::GetNextPosition(double dt) const {
  double speed = 5;
  return Position(m_position.x + m_direction.x() * dt * speed,
		  m_position.y + m_direction.y() * dt * speed);
}


AABB Player::GetAABB() const {
  // bounding box is a bit less then player sprite
  Position min = GetPosition();
  min.x += 0.1;
  min.y += 0.1;
  Position max = GetPosition();
  max.x += 0.9;
  max.y += 0.9;
  return AABB(min,max);
}


AABB Player::GetNextAABB(double dt) const {
  // bounding box is a bit less then player sprite
  Position min = GetNextPosition(dt);
  min.x += 0.1;
  min.y += 0.1;
  Position max = GetNextPosition(dt);
  max.x += 0.9;
  max.y += 0.9;
  return AABB(min,max);
}


void Player::PerformAction(PA::PlayerAction action) {
  m_current_action_start_time = SDL_GetTicks();

  if (action == PA::GoLeft) {
    m_direction.SetX(-1);
  }
  else if (action == PA::GoRight) {
    m_direction.SetX(1);
  }
  else if (action == PA::GoUp) {
    m_direction.SetY(1);
  }
  else if (action == PA::GoDown) {
    m_direction.SetY(-1);
  }
  else if (action == PA::GoNowhere) {
    m_direction.Set(0,0);
  }
  else {
    
  }
}


void Player::StopAction(PA::PlayerAction action) {
  m_current_action_start_time = SDL_GetTicks();

  const double epsilon = 0.01;  // close to 0 but not 0. Just in case :)
  if (action == PA::GoLeft && m_direction.x()<epsilon) {
    m_direction.SetX(0);
  }
  else if (action == PA::GoRight && m_direction.x()>epsilon) {
    m_direction.SetX(0);
  }
  else if (action == PA::GoUp && m_direction.y()>epsilon) {
    m_direction.SetY(0);
  }
  else if (action == PA::GoDown && m_direction.y()<epsilon) {
    m_direction.SetY(0);
  }
  else {
    
  }
}
