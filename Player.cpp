#include "Engine.h"
#include "Player.h"
#include "BombCreator.h"


Player::Player(size_t id, Position initial_position, PT::PlayerType type, PlayerControllerPtr controller) 
  : m_id(id),
    m_position(initial_position),
    m_direction(0,0),
    m_type(type),
    m_current_action_start_time(SDL_GetTicks()),
    m_is_dying(false),
    m_all_bomb_count(g_bomb_player_has_at_start),
    m_fire_range(g_fire_range_player_has_at_start) {

  SetController(controller);

}


void Player::Draw() {
  TexCoords tc = Engine::Get().Scripts()->GetPlayerSprite(GetType(), 
							GetDirection(), 
							IsDying(), 
							SDL_GetTicks() - m_current_action_start_time);

//   std::cerr << "type = " << GetType() << ", direction = " << GetDirection().x() << ", " << GetDirection().y()
// 	    << ", is dying = " << IsDying() << "dt = " << SDL_GetTicks() - m_current_action_start_time << "\n";
//   std::cerr << "tc = " << tc.left << ", " << tc.bottom << ", " << tc.width << ", " << tc.height << "\n";

  Engine::Get().Renderer()->DrawSprite(tc, GetPosition());
}


void Player::Update(const DataForController& /* data */, double dt) {
  m_position = GetNextPosition(dt); // (1)

  PerformAction(GetController()->GetNextAction()); // (2)
  GetController()->ResetNextAction();

  // (1) & (2) must be in that order. Otherwise it is possible to walk
  // through the walls by pressing keys quickly
}


void Player::GivePowerup(PowerupPtr powerup) {
  powerup->Affect(*this);
}


Position Player::GetNextPosition(double dt) const {
  const double speed = 7;
  const Position pos = GetPosition();
  const Direction dir = GetDirection();
  return Position(pos.x + dir.x() * dt * speed,
		  pos.y + dir.y() * dt * speed);
}


AABB Player::GetAABB() const {
  // bounding box is a bit less then player sprite
  const Position pos = GetPosition();
  const Position min = pos - Position( .4, .4);
  const Position max = pos + Position( .4, .25);
  return AABB(min,max);
}


AABB Player::GetNextAABB(double dt) const {
  // bounding box is a bit less then player sprite
  const Position pos = GetNextPosition(dt);
  const Position min = pos - Position( .4, .4);
  const Position max = pos + Position( .4, .25);
  return AABB(min,max);
}


void Player::PerformAction(PA::PlayerAction action) {
  if (action != PA::None) {
    m_current_action_start_time = SDL_GetTicks();
  }

  const double epsilon = 0.01;  // close to 0 but not 0. Just in case :)

  // "Go" actions
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
  // "Stop" Actions
  else if (action == PA::StopGoLeft && m_direction.x()<epsilon) {
    m_direction.SetX(0);
  }
  else if (action == PA::StopGoRight && m_direction.x()>epsilon) {
    m_direction.SetX(0);
  }
  else if (action == PA::StopGoUp && m_direction.y()>epsilon) {
    m_direction.SetY(0);
  }
  else if (action == PA::StopGoDown && m_direction.y()<epsilon) {
    m_direction.SetY(0);
  }
  // "Bomb" actions
  else if (action == PA::PlaceBomb) {
    AddCreator(CreatorPtr(new BombCreator(GetId(), GetPosition(), GetFireRange())));
  }
  // Other Actions
  else if (action == PA::None) {

  }
  else {
    std::cerr << "Got unknown action! [" << action << "]\n";
  }
}


bool Player::HandleInput(const SDL_Event& event) {
  return GetController()->HandleInput(event);
}
