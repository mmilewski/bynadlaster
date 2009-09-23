#ifndef __FIRERANGEPOWERUP_H_INCLUDED__
#define __FIRERANGEPOWERUP_H_INCLUDED__

#include "Powerup.h"


class FireRangePowerup : public Powerup {
public:
  FireRangePowerup(Position position)
    : Powerup(position) {
  }

  void Affect(Player& player) { player.IncreaseFireRange(); }

protected:
  void DoDraw() const;
  void DoUpdate(double dt);
};

#endif
