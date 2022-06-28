#include <iostream>
#include "brick_wall.h"
#include "constants.h"

BrickWall::BrickWall(int brick_width, int brick_height, int brick_rows, int brick_cols, int brick_gap) 
    : brick_width(brick_width), brick_height(brick_height), brick_rows(brick_rows), 
    brick_cols(brick_cols), brick_gap(brick_gap) {
  Populate();
}

void BrickWall::Populate() {
 int y = k_brick_gap+k_brick_width;
 for (int row=0; row<brick_rows; row++) {
   int x = k_brick_gap+k_brick_width;
   for (int col=0; col<brick_cols-2; col++) {
     bricks.push_back(Brick(x, y, k_brick_width, k_brick_height, k_color_brick, k_brick_value));
     x += (k_brick_width+k_brick_gap); 
   }
   y += (k_brick_height+k_brick_gap);
 } 
}

bool BrickWall::Destroyed() {
  for (auto &brick : bricks) {
    if (brick.get_exists()) {
      return false;
    }
  }
  return true;
}