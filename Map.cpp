#include "Map.h"
#include "Renderer.h"
#include "StdAfx.h"


Map::Map(size_t width, size_t height)
  : m_width(width), m_height(height) {
  m_map = boost::multi_array<FT::FieldType, 2>(boost::extents[GetHeight()][GetWidth()]);

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
  switch(type) {
  case FT::Floor:
    Renderer::Get().DrawSprite(Position(x/static_cast<double>(GetWidth()),
                                        y/static_cast<double>(GetHeight()),
                                        16.0/1024,
                                        16.0/1024),
                               TexCoords(367.0/1024, 125.0/1024, 16.0/1024, 16.0/1024) );
    break;
  case FT::Box:
    break;
  case FT::Wall:
    break;
  }
  #warning zaimplementować powyższe
}
