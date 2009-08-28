#ifndef __BOMB_H_INCLUDED__
#define __BOMB_H_INCLUDED__

#include "Object.h"


class Bomb : public Object {
public :
  explicit Bomb(Position position);
    
protected:
  void DoDraw();
  void DoUpdate(double dt);
  OT::ObjectType DoGetType() const { return OT::BOMB; }
  Position DoGetPosition() const { return m_position; }
  
private:
  size_t m_anim_frame_num;
  Position m_position;
};


#endif
