#ifndef __BOMB_H_INCLUDED__
#define __BOMB_H_INCLUDED__

#include "Object.h"


class Bomb : public Object {
public :
  explicit Bomb(size_t owner_id, Position position, int explosion_range);
  void Detonate();
    
protected:
  void DoDraw() const;
  void DoUpdate(double dt);
  OT::ObjectType DoGetType() const { return OT::Bomb; }
  Position DoGetPosition() const { return m_position; }
  AABB DoGetAABB() const { return m_aabb; }
  
private:
  size_t m_anim_frame_num;
  Position m_position;
  double m_time_from_last_frame_switch;
  AABB m_aabb;
  size_t m_owner_id;
  size_t m_explision_range;
  double m_living_time;
};

typedef boost::shared_ptr<Bomb> BombPtr;


#endif
