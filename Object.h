#ifndef __OBJECT_H_INCLUDED__
#define __OBJECT_H_INCLUDED__

#include "StdAfx.h"
#include "AABB.h"
#include "Types.h"
#include "Creator.h"


class Object {
public:
  virtual ~Object() {}
  
  void Draw()  { DoDraw(); }
  void Update(double dt)  { DoUpdate(dt); }
  OT::ObjectType GetType() const  { return DoGetType(); }
  Position GetPosition() const  { return DoGetPosition(); }
  AABB GetAABB() const  { return DoGetAABB(); }
  bool IsAlive() const  { return m_is_alive; }
  void SetAliveFlag(bool flag)  { m_is_alive = flag; }
  std::list<CreatorPtr>& GetAllCreators()  { return m_creators; }

protected:
  void AddCreator(CreatorPtr creator)  { m_creators.insert(m_creators.end(), creator); }
  virtual void DoDraw() = 0;
  virtual void DoUpdate(double dt) = 0;
  virtual OT::ObjectType DoGetType() const = 0;
  virtual Position DoGetPosition() const = 0;
  virtual AABB DoGetAABB() const = 0;

private:
  bool m_is_alive;   // if false, then object should be swept out/garbaged
  std::list<CreatorPtr> m_creators;
};

typedef boost::shared_ptr<Object> ObjectPtr;

#endif
