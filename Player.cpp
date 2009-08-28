#include "Renderer.h"
#include "Player.h"


Player::Player(Position initial_position) 
  : m_position(initial_position),
    m_direction(0,0) {
}


void Player::Draw() {
  Renderer::Get().DrawSprite(Position(m_position.x, m_position.y), TexCoords(0, 218, 20, 22));
}


void Player::Update(double dt) {
  m_position = GetNextPosition(dt);
}


Position Player::GetNextPosition(double dt) const {
  double speed = 5;
  return Position(m_position.x + m_direction.x() * dt * speed,
		  m_position.y + m_direction.y() * dt * speed);
}


void Player::PerformAction(PA::PlayerAction action) {
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
  else {
    
  }
}


void Player::StopAction(PA::PlayerAction action) {
  if (action == PA::GoLeft) {
    m_direction.SetX(0);
  }
  else if (action == PA::GoRight) {
    m_direction.SetX(0);
  }
  else if (action == PA::GoUp) {
    m_direction.SetY(0);
  }
  else if (action == PA::GoDown) {
    m_direction.SetY(0);
  }
  else {
    
  }
}
