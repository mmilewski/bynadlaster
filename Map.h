#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__


#include <boost/multi_array.hpp>
#include "StdAfx.h"


class Map {
public:
  explicit Map(size_t width, size_t height);

  void Draw();
  void Update(double dt);
  void Load();

  size_t GetWidth() const { return m_width; }
  size_t GetHeight() const { return m_height; }

  bool IsFieldStandable(const Position& field_position) const;

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
