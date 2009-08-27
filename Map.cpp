#include "Map.h"
#include "Renderer.h"
#include "StdAfx.h"


Map::Map(size_t width, size_t height)
  : m_width(width), m_height(height),
    m_map(boost::multi_array<FT::FieldType, 2>(boost::extents[height][width]))
{
  for (size_t y = 0; y < GetHeight(); ++y) {
    for (size_t x = 0; x < GetWidth(); ++x) {
      m_map[y][x] = FT::Floor;
    }
  }
}


void Map::Draw() {
  for (size_t y = 0; y < GetHeight(); ++y) {
    for (size_t x = 0; x < GetWidth(); ++x) {
      DrawTile(x, y, m_map[y][x]);
    }
  }
}


void Map::Update(double /* dt */) {

}


void Map::Load() {

}


void Map::DrawTile(size_t x, size_t y, FT::FieldType type) {
  
  // UWAGA. programy graficzne zwykle umieszczają początek układu współrzędnych w
  // lewym górnym rogu a texcoord (0,0) oznacza lewy dolny narożnik, więc drugi
  // argument TexCoord należy odjąć od jedności. Life is life ;)

  // UWAGA. rozmiary kafla na ekranie. Jeżeli ekran nie będzie kwadratowy, to kafle również
  // nie będą kwadratowe. Najlepiej byłoby mieć dostęp do parametru ratio (width/height)
  // okna - wtedy wystarczy ustawić np. tile_width=window_ratio/GetWidth()
  double tile_width=1.0/GetWidth(), tile_height=1.0/GetHeight();
  Position tile_position(x/static_cast<double>(GetWidth()),
                         y/static_cast<double>(GetHeight()),
                         tile_width,
                         tile_height);
  switch(type) {
  case FT::Floor:
    Renderer::Get().DrawSprite(tile_position, TexCoords(367.0/1024, 1-126.0/1024, 16.0/1024, 16.0/1024) );
    break;
  case FT::Box:
    Renderer::Get().DrawSprite(tile_position, TexCoords(399.0/1024, 1-126.0/1024, 16.0/1024, 16.0/1024) );
    break;
  case FT::Wall:
    Renderer::Get().DrawSprite(tile_position, TexCoords(415.0/1024, 1-126.0/1024, 16.0/1024, 16.0/1024) );
    break;
  }
}
