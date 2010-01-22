#include "AABB.h"


bool AABB::CollidesWith(const AABB& other) const {
	// this method is cool, isn't it?
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


bool AABB::WhetherIncludes(const AABB& other) const {
  const double t_min_x = this->GetMin().x;
  const double t_max_x = this->GetMax().x;
  const double t_min_y = this->GetMin().y;
  const double t_max_y = this->GetMax().y;
  const double o_min_x = other.GetMin().x;
  const double o_max_x = other.GetMax().x;
  const double o_min_y = other.GetMin().y;
  const double o_max_y = other.GetMax().y;

  // if other is inside of this return true
  return (t_min_x<o_min_x && t_max_x>o_max_x && t_min_y<o_min_y && t_max_y>o_max_y);
}


bool AABB::IntersectsUsingDirectionWith(const AABB& other, const Direction& dir) const {
  const double t_min_x = this->GetMin().x;
  const double t_max_x = this->GetMax().x;
  const double t_min_y = this->GetMin().y;
  const double t_max_y = this->GetMax().y;
  const double o_min_x = other.GetMin().x;
  const double o_max_x = other.GetMax().x;
  const double o_min_y = other.GetMin().y;
  const double o_max_y = other.GetMax().y;

  // on inlusion there is no intersection, isn't it
  if (this->WhetherIncludes(other) || other.WhetherIncludes(*this) ) {
    return false;
  }

  // AABBs are separated (and there is no inclusion)
  if (t_min_x>o_max_x || t_max_x<o_min_x || t_min_y>o_max_y || t_max_y<o_min_y) {
    return false;  // no collision
  }

  const double dir_x = dir.GetX();  // x<0 means going left
  const double dir_y = dir.GetY();  // y<0 means going down

  if (dir_x>0 && t_max_x>o_max_x)
    return false;

  if (dir_x<0 && t_min_x<o_min_x)
    return false;

  if (dir_y>0 && t_max_y>o_max_y)
    return false;

  if (dir_y<0 && t_min_y<o_min_y)
    return false;

  return true;
}



std::ostream& operator<< (std::ostream& os, const AABB& aabb) {
  os << "[ min: " << aabb.GetMin() << ", max: " << aabb.GetMax() << ']';
  return os;
}
