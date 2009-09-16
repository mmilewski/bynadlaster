#ifndef __POWERUP_H_INCLUDED__
#define __POWERUP_H_INCLUDED__

#include "Object.h"

class Player;

class Powerup : public Object {
public :
  explicit Powerup(Position position);
  virtual ~Powerup() {}
  virtual void Affect(Player& player) = 0;

protected:
//   virtual void DoDraw() const = 0;			// is that useless?
//   virtual void DoUpdate(double dt) = 0;
  OT::ObjectType DoGetType() const { return OT::Powerup; }
  virtual Position DoGetPosition() const { return m_position; }
  virtual AABB DoGetAABB() const { return m_aabb; }
  
private:
  Position m_position;
  AABB m_aabb;
};

typedef boost::shared_ptr<Powerup> PowerupPtr;

#endif
