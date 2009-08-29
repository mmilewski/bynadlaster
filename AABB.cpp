#include "AABB.h"

bool AABB::CollidesWith(const AABB& other) {
  double const t_min_x = this->GetMin().x;
  double const t_max_x = this->GetMax().x;
  double const t_min_y = this->GetMin().y;
  double const t_max_y = this->GetMax().y;
  double const o_min_x = other.GetMin().x;
  double const o_max_x = other.GetMax().x;
  double const o_min_y = other.GetMin().y;
  double const o_max_y = other.GetMax().y;

  if( t_min_x>o_max_x || t_max_x<o_min_x || t_min_y>o_max_y || t_max_y<o_min_y )
    return false;
  return true;
}
