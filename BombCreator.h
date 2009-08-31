#ifndef __BOMBCREATOR_H_INCLUDED__
#define __BOMBCREATOR_H_INCLUDED__

#include "Creator.h"


class BombCreator : public Creator {
public:
  explicit BombCreator(Position initial_position);
  void Create(Game& game);

  const Position& GetPosition() const { return m_position; }

private:
  Position m_position;
};

#endif
