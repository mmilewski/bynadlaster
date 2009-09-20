#ifndef __NON_ENTITY_H_INLCUDED__
#define __NON_ENTITY_H_INLCUDED__

#include "StdAfx.h"

// This should be named "Object", but this name is already taken by
// Entity class (called Object). If you can find better name for
// NonEntity class then refactor it
class NonEntity {
public:
  explicit NonEntity() : m_is_alive(true) { }
  virtual ~NonEntity() { }
  
  void Draw() const { DoDraw(); }
  void Update(double dt) { DoUpdate(dt); }

  bool IsAlive() const { return m_is_alive; }
  void SetAliveFlag(bool is_alive) { m_is_alive = is_alive; }

//protected: // public needed in AnimatedText::RegisterInLua
public:
  virtual void DoDraw() const = 0;
  virtual void DoUpdate(double dt) = 0;

private:
  bool m_is_alive;
};

typedef boost::shared_ptr<NonEntity> NonEntityPtr;


#endif
