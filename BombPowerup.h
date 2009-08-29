#ifndef __BOMBPOWERUP_H_INCLUDED__
#define __BOMBPOWERUP_H_INCLUDED__

#include "Powerup.h"


class BombPowerup : public Powerup {
public:
  BombPowerup(Position position)
    : Powerup(position) {
  }

  void Affect(Player& player) { player.IncreaseBombCount(); }

protected:
  void DoDraw();
  void DoUpdate(double dt);
};

#endif
