#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include <boost/noncopyable.hpp>

#include "Color.h"
#include "StdAfx.h"


class Renderer : boost::noncopyable {
public:
  void LoadTexture(std::string filename);

  void DrawSprite(Position pos, TexCoords tc, Size ts);
  void DrawSprite(Position pos, TexCoords tc);

  void DrawSpriteAbsolute(Position pos, TexCoords tc, Size ts);
  void DrawSpriteAbsolute(Position pos, TexCoords tc, Size size, Color color);

  void SetTileSize(Size size)  { m_tile_width = size.width; m_tile_height = size.height; }
  
  static Renderer& Get() {
    static Renderer s_instance;
    return s_instance;
  }

protected:
  SDL_Surface* flip(SDL_Surface *in, bool x, bool y, bool rgba);

private:
  double m_tile_width;
  double m_tile_height;
};

#endif
