#ifndef __BOXINFIRE_H_INCLUDED__
#define __BOXINFIRE_H_INCLUDED__

#include "NonEntity.h"

class BoxInFire : public NonEntity {
public:
  explicit BoxInFire(Position position);
  void DoDraw() const;
  void DoUpdate(double dt);

private:
  Position m_position;
  const size_t m_anim_frames_count;        // number of frames in whole animation
  const double m_frame_duration_time;     // (in seconds)
  size_t m_current_anim_frame;
  double m_current_frame_duration_time;
};

#endif
