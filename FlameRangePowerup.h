#ifndef __FLAMERANGEPOWERUP_H_INCLUDED__
#define __FLAMERANGEPOWERUP_H_INCLUDED__

#include "Powerup.h"


class FlameRangePowerup : public Powerup {
public:
  FlameRangePowerup(Position position)
    : Powerup(position) {
  }

  void Affect(Player& player) { player.IncreaseFlameRange(); }

protected:
  void DoDraw() const;
  void DoUpdate(double dt);
};

#endif
