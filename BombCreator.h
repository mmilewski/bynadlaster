#ifndef __BOMBCREATOR_H_INCLUDED__
#define __BOMBCREATOR_H_INCLUDED__

#include "Creator.h"


class BombCreator : public Creator {
public:
  explicit BombCreator(size_t owner_id, Position initial_position, size_t range);
  void Create(Game& game);

  const Position& GetPosition() const { return m_position; }

private:
  size_t m_owner_id;
  Position m_position;
  size_t m_range;
};

#endif
