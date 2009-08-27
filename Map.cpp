#include "Map.h"


Map::Map(size_t width, size_t height) {
  m_map = boost::multi_array<FT::FieldType, 2>(boost::extents[height][width]);

  for (size_t y = 0; y < g_max_map_height; ++y) {
    for (size_t x = 0; x < g_max_map_width; ++x) {
      m_map[y][x] = FT::Floor;
    }
  }
}


void Map::Draw() {
  for (size_t y = 0; y < g_max_map_height; ++y) {
    for (size_t x = 0; x < g_max_map_width; ++x) {
      DrawTile(x, y);
    }
  }
}


void Map::Update(double /* dt */) {

}


void Map::Load() {

}


void Map::DrawTile(size_t x, size_t y) {
  
}
