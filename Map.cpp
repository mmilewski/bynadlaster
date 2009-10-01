#include "Engine.h"
#include "Map.h"
#include "StdAfx.h"


Map::Map(size_t width, size_t height)
  : m_map(boost::multi_array<FT::FieldType, 2>(boost::extents[height][width])),
    m_width(width), m_height(height)  {

  for (size_t y = 0; y < GetHeight(); ++y) {
    for (size_t x = 0; x < GetWidth(); ++x) {
      m_map[y][x] = FT::Floor;
    }
  }
  m_map[3][6] = m_map[3][5] = m_map[3][4] = m_map[3][3] = m_map[3][2] = FT::Wall;
  m_map[1][6] = m_map[1][5] = m_map[1][3] = m_map[1][2] = FT::Wall;

  m_map[7][9] = m_map[7][5] = m_map[5][7] = m_map[9][7] = FT::Box;
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
  if (x<0 || static_cast<size_t>(x)>=GetWidth() || y<0 || static_cast<size_t>(y)>=GetHeight())
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
      Engine::Get().Renderer()->DrawSprite(TexCoords(383.0, 126.0, 16.0, 16.0), tile_position);
    }
    else {
      Engine::Get().Renderer()->DrawSprite(TexCoords(367.0, 126.0, 16.0, 16.0), tile_position);
    }
    break;
  case FT::Box:
    Engine::Get().Renderer()->DrawSprite(TexCoords(399.0, 126.0, 16.0, 16.0), tile_position);
    if (g_render_aabbs)
      Engine::Get().Renderer()->DrawAABB(GetFieldAABB(x,y));
    break;
  case FT::Wall:
    Engine::Get().Renderer()->DrawSprite(TexCoords(415.0, 126.0, 16.0, 16.0), tile_position);
    break;
  }
}


void Map::DrawBorder() {
  RendererPtr renderer = Engine::Get().Renderer();

  // right border
  for (int i = GetHeight()+1; i > 0; --i) {
    renderer->DrawSprite(TexCoords(495.0, 126.0, 16.0, 16.0), Position(2 + GetWidth()+1, i));
    renderer->DrawSprite(TexCoords(671.0, 126.0, 16.0, 16.0), Position(2 + GetWidth()+1 + 1, i));
  }
  renderer->DrawSprite(TexCoords(367.0, 142.0, 16.0, 16.0), Position(2 + GetWidth()+1 + 1, 0));

  // left border
  for (size_t i = GetHeight()+1; i > 0; --i) {
    renderer->DrawSprite(TexCoords(623.0, 126.0, 16.0, 16.0), Position(2 + 0, i));
    renderer->DrawSprite(TexCoords(455.0, 142.0, 16.0, 16.0), Position(2 + 0 - 1, i));
  }
  renderer->DrawSprite(TexCoords(471.0, 142.0, 16.0, 16.0), Position(2 + 0 - 1, 0));

  // top corners
  renderer->DrawSprite(TexCoords(431.0, 126.0, 16.0, 16.0), Position(2, GetHeight()+1)); // top left
  renderer->DrawSprite(TexCoords(479.0, 126.0, 16.0, 16.0), Position(2 + GetWidth()+1, GetHeight()+1)); // top right
  
  // top border
  for (size_t i = 0; i < GetWidth(); i += 2) {
    renderer->DrawSprite(TexCoords(448.0, 126.0, 16.0, 16.0), Position(2 + 1 + i, GetHeight()+1));
  }
  for (size_t i = 1; i < GetWidth(); i += 2) {
    renderer->DrawSprite(TexCoords(463.0, 126.0, 16.0, 16.0), Position(2 + 1 + i, GetHeight()+1));
  }

  // bottom border
  for (size_t i = 0; i < GetWidth()+2; ++i) {
    renderer->DrawSprite(TexCoords(543.0 + 16 * (i % 5), 126.0, 16.0, 16.0), Position(2 + i, 0));
  }
}
