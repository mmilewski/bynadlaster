#include "AABB.h"


bool AABB::CollidesWith(const AABB& other) {
  const double t_min_x = this->GetMin().x;
  const double t_max_x = this->GetMax().x;
  const double t_min_y = this->GetMin().y;
  const double t_max_y = this->GetMax().y;
  const double o_min_x = other.GetMin().x;
  const double o_max_x = other.GetMax().x;
  const double o_min_y = other.GetMin().y;
  const double o_max_y = other.GetMax().y;

  if( t_min_x>o_max_x || t_max_x<o_min_x || t_min_y>o_max_y || t_max_y<o_min_y )
    return false;
  return true;
}


bool AABB::CollidesUsingDirectionWith(const AABB& other, const Direction& dir) {
  const double t_min_x = this->GetMin().x;
  const double t_max_x = this->GetMax().x;
  const double t_min_y = this->GetMin().y;
  const double t_max_y = this->GetMax().y;
  const double o_min_x = other.GetMin().x;
  const double o_max_x = other.GetMax().x;
  const double o_min_y = other.GetMin().y;
  const double o_max_y = other.GetMax().y;

  if (t_min_x>o_max_x || t_max_x<o_min_x || t_min_y>o_max_y || t_max_y<o_min_y) {
    return false;  // no collision
  }

#warning implement CollidesUsingDirectionWith

  return true; // was this missing??
}
