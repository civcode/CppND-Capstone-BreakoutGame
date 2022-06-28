#ifndef BALL_H
#define BALL_H

#include <vector>

#include "block.h"
#include "misc.h"

class Ball : public Block {
  private:

  float pos_x;
  float pos_y;
  float velocity_x;
  float velocity_y;
  bool is_released = false;
  int released_count;

  public:
  
  Ball(int x, int y, int w, int h, float velocity_x, float velocity_y, Color color);
 
  float get_pos_x();
  float get_pos_y();

  float get_velocity_x();
  float get_velocity_y();
  void set_velocity(float v_x, float v_y);

  void set_x(int x);
  void set_y(int y);
  
  
  bool get_released();
  void set_released(bool is_released);
  int get_released_count();

  void ChangeDirection(Block::CollisionType collision_type, float deflection = 0.0);
  void Update();
  
};

#endif // BALL_H