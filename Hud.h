#ifndef __HUD_H_INCLUDED__
#define __HUD_H_INCLUDED__

#include "StdAfx.h"

class Hud {
public:
  void Draw();
  void Update(double dt);
};


typedef boost::shared_ptr<Hud> HudPtr;


#endif
