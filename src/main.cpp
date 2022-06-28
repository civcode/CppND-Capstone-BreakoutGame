#include <iostream>
#include <vector>

#include "ball.h"
#include "brick.h"
#include "brick_wall.h"
#include "controller.h"
#include "constants.h"
#include "game.h"
#include "racket.h"
#include "renderer.h"


int main() {

  Racket racket((kScreenWidth-k_racket_width)/2, 
                 kScreenHeight-k_infobar_height, 
                 k_racket_width, 
                 k_racket_height, 
                 k_color_racket);
  
  Ball ball((kScreenWidth-k_ball_width)/2,
             kScreenHeight-k_infobar_height-k_racket_height, 
             k_ball_width, 
             k_ball_width, 
             0.0,
             0.0,
             k_color_ball);

  BrickWall wall(k_brick_width, 
                   k_brick_height, 
                   k_brick_wall_rows, 
                   k_brick_wall_cols, 
                   k_brick_gap);

 
  Renderer renderer(kScreenWidth, kScreenHeight);
  Controller controller;
  Game game(racket, ball, wall);
  game.Run(controller, renderer, kMsPerFrame);
  return 0;
}