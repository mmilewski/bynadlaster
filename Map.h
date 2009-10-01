#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include <boost/multi_array.hpp>
#include "StdAfx.h"
#include "AABB.h"


class Map {
public:
  explicit Map(size_t width, size_t height);

  void Draw();
  void Update(double dt);
  void Load();

  size_t GetWidth() const { return m_width; }
  size_t GetHeight() const { return m_height; }
  FT::FieldType GetFieldType(size_t x, size_t y) const  { return y<GetHeight() && x<GetWidth() ? m_map[y][x] : FT::Wall; }
  void SetFieldType(size_t x, size_t y, FT::FieldType type)  { m_map[y][x] = type; }
  Position GetFieldPosition(size_t x, size_t y) const  { return Position(x+3, y+1); }
  AABB GetFieldAABB(size_t x, size_t y) const  { return AABB(GetFieldPosition(x, y) + Position( .0,  .0),
                                                             GetFieldPosition(x, y) + Position(1.0, 1.0)); }

  Position PositionToPositionOnMap(const Position& position) const;

  bool IsFieldStandable(const Position& field_position) const;
  bool IsFieldStandable(double posx, double posy) const;

protected:
  void DrawTile(size_t x, size_t y, FT::FieldType type);
  void DrawBorder();

private:
  boost::multi_array<FT::FieldType, 2> m_map;
  size_t m_width;
  size_t m_height;
  
};


typedef boost::shared_ptr<Map> MapPtr;


#endif
