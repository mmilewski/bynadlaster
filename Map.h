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


protected:
  void DrawTile(size_t x, size_t y);

private:
  boost::multi_array<FT::FieldType, 2> m_map;
  
};


#endif
