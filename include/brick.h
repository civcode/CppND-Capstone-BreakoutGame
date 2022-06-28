#ifndef BRICK_H
#define BRICK_H

#include "block.h"
#include "ball.h"

class Brick : public Block {
  private:
  int value;
  bool exists;
  
  public:
  Brick(int x, int y, int w, int h, Color color, int value);

  int get_value();

  bool get_exists();
  void set_exists(bool exists);
                    
};

#endif //BRICK_H