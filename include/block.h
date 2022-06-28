#ifndef BLOCK_H
#define BLOCK_H

#include "misc.h"

class Block {
  protected:
  int x;
  int y;
  int w;
  int h;
  Color color;
  
  public:
  enum class CollisionType { kTop, kBottom, kLeft, kRight };

  Block(int x, int y, int w, int h, Color color) : x(x), y(y), w(w), h(h), color(color) {};

  int get_x() const; 
  int get_y() const;
  int get_w() const; 
  int get_h() const;

  Color get_color(); 

  bool DetectCollision(Block &other, CollisionType &collision_type, int *overlap = nullptr);
  bool ContainsPoint(int x, int y);

};

#endif //BLOCK_H