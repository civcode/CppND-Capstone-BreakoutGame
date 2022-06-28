#ifndef RACKET_H
#define RACKET_H

#include "ball.h"
#include "block.h"
#include "misc.h"

class Racket : public Block {
  private:

  public:
  enum class Direction { kLeft, kRight };
  
  Racket(int x, int y, int w, int h, Color color) : Block(x, y, w, h, color) { };

  void set_x(int x) { this->x = x; };

};

#endif //RACKET_H