#ifndef __OBJECT_H_INCLUDED__
#define __OBJECT_H_INCLUDED__

#include "StdAfx.h"


namespace OT {
  enum ObjectType {
    ENEMY,
    FIRE,
    POWERUP,
    BOMB
  };
}

class Object {
public:
  virtual ~Object() {}
  
  void Draw()  { DoDraw(); }
  void Update(double dt)  { DoUpdate(dt); }
  OT::ObjectType GetType() const  { return DoGetType(); }
  Position GetPosition() const  { return DoGetPosition(); }

protected: 
  virtual void DoDraw() = 0;
  virtual void DoUpdate(double dt) = 0;
  virtual OT::ObjectType DoGetType() const = 0;
  virtual Position DoGetPosition() const = 0;
};

typedef boost::shared_ptr<Object> ObjectPtr;

#endif
