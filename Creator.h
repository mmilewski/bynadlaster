#ifndef __CREATOR_H_INCLUDED__
#define __CREATOR_H_INCLUDED__


class Game;

class Creator {
public:
  virtual void Create(Game& game) = 0;
};


typedef boost::shared_ptr<Creator> CreatorPtr;

#endif
