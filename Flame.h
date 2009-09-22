#ifndef __FLAME_H_INCLUDED__
#define __FLAME_H_INCLUDED__

#include "Object.h"

struct FD {
  enum FlameDirection {
    Up,
    Left,
    Down,
    Right,
    Center
  };
};


class Flame : public Object {
public :
  explicit Flame(Position position, Size size, FD::FlameDirection direction);
    
protected:
  void DoDraw() const;
  void DoUpdate(double dt);
  OT::ObjectType DoGetType() const { return OT::Fire; }
  Position DoGetPosition() const { return m_position; }
  AABB DoGetAABB() const { return m_aabb; }
  
private:
  Position m_position;
  AABB m_aabb;
  Size m_size;
  FD::FlameDirection m_direction;
  size_t m_anim_frame_num;
  double m_time_from_last_frame_switch;
};

typedef boost::shared_ptr<Flame> FlamePtr;


#endif
