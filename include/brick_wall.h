#ifndef BRICKWALL_H
#define BRICKWALL_H

#include <vector>
#include "ball.h"
#include "brick.h"

class BrickWall {
  private:
  int brick_width;
  int brick_height;
  int brick_rows;
  int brick_cols;
  int brick_gap;
  
  public:
  std::vector<Brick> bricks;
  
  BrickWall(int brick_width, int brick_height, int brick_rows, int brick_cols, int brick_gap);
   
  void Populate();
  void DetectCollision(Ball &ball);
  void HandleCollision();
  bool Destroyed();
  
};

#endif // BRICKWALL_H