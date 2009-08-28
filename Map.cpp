#include "Map.h"
#include "Renderer.h"
#include "StdAfx.h"


Map::Map(size_t width, size_t height)
  : m_map(boost::multi_array<FT::FieldType, 2>(boost::extents[height][width])),
    m_width(width), m_height(height)  {
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
  Position tile_position(x, y);

//   switch(type) {
//   case FT::Floor:
    Renderer::Get().DrawSprite(tile_position, TexCoords(367.0, 126.0, 16.0, 16.0));
//     break;
//   case FT::Box:
//     Renderer::Get().DrawSprite(tile_position, TexCoords(399.0, 126.0, 16.0, 16.0));
//     break;
//   case FT::Wall:
//     Renderer::Get().DrawSprite(tile_position, TexCoords(415.0, 126.0, 16.0, 16.0));
//     break;
//   }
}
