#ifndef __FLAME_CREATOR_H_INCLUDED__
#define __FLAME_CREATOR_H_INCLUDED__

#include "Creator.h"


class FlameCreator : public Creator {
public:
  explicit FlameCreator(size_t owner_id, Position initial_position, size_t range);
  void Create(Game& game);
  
  const Position& GetPosition() const  { return m_position; }
  int GetRange() const  { return m_range; }

protected:
  void AddFlame(double xpos, double ypos);

private:
  size_t m_owner_id;
  Position m_position;
  size_t m_range;
};

#endif
