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
  m_map[6][6] = FT::Wall;
}


void Map::Draw() {
  for (size_t y = 0; y < GetHeight(); ++y) {
    for (size_t x = 0; x < GetWidth(); ++x) {
      DrawTile(x, y, m_map[y][x]);
    }
  }
  DrawBorder();
}


void Map::Update(double /* dt */) {

}


void Map::Load() {

}

Position Map::PositionToPositionOnMap(const Position& position) const {
  return Position(floor(position.x-3), floor(position.y-1));
}


bool Map::IsFieldStandable(const Position& field_position) const {
  const Position on_map_pos = PositionToPositionOnMap(field_position);
  const int x = on_map_pos.x;
  const int y = on_map_pos.y;
  if (x<0 || static_cast<unsigned>(x)>=GetWidth() || y<0 || static_cast<unsigned>(y)>=GetHeight())
    return false;

  return m_map[y][x]==FT::Floor;
}


bool Map::IsFieldStandable(double posx, double posy) const {
  return IsFieldStandable(Position(posx, posy));
}


void Map::DrawTile(size_t x, size_t y, FT::FieldType type) {
  const Position tile_position = Position(x+3, y+1);

  switch(type) {
  case FT::Floor:
    if (y == GetHeight()-1 || (y < GetHeight()-1 && m_map[y+1][x] != FT::Floor)) {
      Renderer::Get().DrawSprite(tile_position, TexCoords(383.0, 126.0, 16.0, 16.0));
    }
    else {
      Renderer::Get().DrawSprite(tile_position, TexCoords(367.0, 126.0, 16.0, 16.0));
    }
    break;
  case FT::Box:
    Renderer::Get().DrawSprite(tile_position, TexCoords(399.0, 126.0, 16.0, 16.0));
    break;
  case FT::Wall:
    Renderer::Get().DrawSprite(tile_position, TexCoords(415.0, 126.0, 16.0, 16.0));
    break;
  }
}


void Map::DrawBorder() {
  // right border
  for (int i = GetHeight()+1; i > 0; --i) {
    Renderer::Get().DrawSprite(Position(2 + GetWidth()+1, i), TexCoords(495.0, 126.0, 16.0, 16.0));
    Renderer::Get().DrawSprite(Position(2 + GetWidth()+1 + 1, i), TexCoords(671.0, 126.0, 16.0, 16.0));
  }
  Renderer::Get().DrawSprite(Position(2 + GetWidth()+1 + 1, 0), TexCoords(367.0, 142.0, 16.0, 16.0));

  // left border
  for (size_t i = GetHeight()+1; i > 0; --i) {
    Renderer::Get().DrawSprite(Position(2 + 0, i), TexCoords(623.0, 126.0, 16.0, 16.0));
    Renderer::Get().DrawSprite(Position(2 + 0 - 1, i), TexCoords(455.0, 142.0, 16.0, 16.0));
  }
  Renderer::Get().DrawSprite(Position(2 + 0 - 1, 0), TexCoords(471.0, 142.0, 16.0, 16.0));

  // top corners
  Renderer::Get().DrawSprite(Position(2, GetHeight()+1), TexCoords(431.0, 126.0, 16.0, 16.0)); // top left
  Renderer::Get().DrawSprite(Position(2 + GetWidth()+1, GetHeight()+1), TexCoords(479.0, 126.0, 16.0, 16.0)); // top right
  
  // top border
  for (size_t i = 0; i < GetWidth(); i += 2) {
    Renderer::Get().DrawSprite(Position(2 + 1 + i, GetHeight()+1), TexCoords(448.0, 126.0, 16.0, 16.0));
  }
  for (size_t i = 1; i < GetWidth(); i += 2) {
    Renderer::Get().DrawSprite(Position(2 + 1 + i, GetHeight()+1), TexCoords(463.0, 126.0, 16.0, 16.0));
  }

  // bottom border
  for (size_t i = 0; i < GetWidth()+2; ++i) {
    Renderer::Get().DrawSprite(Position(2 + i, 0), TexCoords(543.0 + 16 * (i % 5), 126.0, 16.0, 16.0));
  }
  
}
