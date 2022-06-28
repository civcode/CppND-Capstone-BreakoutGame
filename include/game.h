#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>

#include "ball.h"
#include "brick.h"
#include "brick_wall.h"
#include "controller.h"
#include "racket.h"
#include "renderer.h"
#include "SDL.h"

class Game {
 private:
  enum class CollisionObject { kBorderLeft, kBorderRight, kBorderTop, kBorderBottom, kRacket, kBrick };

  int score;
  int lives_count;
  bool level_started;

  Racket racket;
  Ball ball;
  BrickWall wall;
  CollisionObject collision_previous;

  void DetectCollisionBorder(Ball &ball);
  void DetectCollision();
  void BallLost();
  bool CheckStatus(Renderer &renderer, BrickWall &wall, Ball &ball, bool sdl_quit);
  void Update();

  // std::random_device dev;
  // std::mt19937 engine;
  // std::uniform_int_distribution<int> random_w;
  // std::uniform_int_distribution<int> random_h;

  public:
  Game(Racket racket, Ball ball, BrickWall wall); 
  
  void Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration);
  
  int get_score() const;
  
};

#endif