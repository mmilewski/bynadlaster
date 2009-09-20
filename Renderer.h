#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include "StdAfx.h"


class Renderer {
public:
  void LoadTexture(std::string filename);

  void DrawSprite(TexCoords tc, Position pos, Size ts);
  void DrawSprite(TexCoords tc, Position pos);

  void DrawSpriteAbsolute(TexCoords tc, Position pos, Size ts);
  void DrawSpriteAbsolute(TexCoords tc, Position pos, Color color, Size size);

  void DrawQuad(Position pos, Color color, Size size);

  void SetTileSize(Size size)  { m_tile_width = size.width; m_tile_height = size.height; }
  
  void SwapBuffers();

protected:
  SDL_Surface* flip(SDL_Surface *in, bool x, bool y, bool rgba);

private:
  double m_tile_width;
  double m_tile_height;
};

typedef boost::shared_ptr<Renderer> RendererPtr;


#endif
