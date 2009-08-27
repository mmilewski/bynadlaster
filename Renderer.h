#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include <boost/noncopyable.hpp>

#include "StdAfx.h"


class Renderer : boost::noncopyable {
public:
  void LoadTexture(std::string filename);
  void DrawSprite(Position pos, TexCoords texs);
  
  static Renderer& Get() {
    static Renderer s_instance;
    return s_instance;
  }

protected:
  SDL_Surface* flip( SDL_Surface *in, bool x, bool y, bool rgba );
};

#endif
