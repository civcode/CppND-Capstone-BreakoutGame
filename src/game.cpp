#include <iostream>
#include <map>

#include "constants.h"
#include "game.h"
#include "SDL.h"

Game::Game(Racket racket, Ball ball, BrickWall wall) : racket(racket), ball(ball), wall(wall) {
  score = 0;
  lives_count = 3;
  level_started = false;
  collision_previous = Game::CollisionObject::kRacket;
} 

void Game::Run(Controller &controller, Renderer &renderer,
  std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool sdl_quit = false;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(sdl_quit, racket, ball);
    
    // Update element positions
    Update();

    // Detect and process collisions
    //DetectCollision();

    // Render scene
    renderer.Render(racket, ball, wall);


    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000 && ball.get_released_count() > 0) {
      renderer.UpdateWindowTitle(lives_count, score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // Check for end of game
    running = CheckStatus(renderer, wall, ball, sdl_quit);
   
    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

bool Game::CheckStatus(Renderer &renderer, BrickWall &wall, Ball &ball, bool sdl_quit) {
  if (sdl_quit) {
    std::cout << "Game quitted.\n";
    return false;
  } else if (wall.Destroyed() || lives_count == 0) {
    std::string win("Game Over. You Win! Score: " + std::to_string(score));
    std::string lose("Game Over. You Lose. Score: " + std::to_string(score));
    if (lives_count > 0) {
      renderer.UpdateWindowTitle(win);
      std::cout << win << "\n";
    } else {
      renderer.UpdateWindowTitle(lose); 
      std::cout << lose << "\n";
    }
    SDL_Delay(k_exit_game_delay);
    return false;
  }
  return true;
}

void Game::Update() {
  ball.Update();
  DetectCollision();
}
       
void Game::DetectCollision() {
  
  auto type2string = [](Block::CollisionType collision_type){ 
    switch(collision_type) {
      case Block::CollisionType::kTop:
        return std::string("kTop"); break;
      case Block::CollisionType::kBottom:
        return std::string("kBottom"); break;
      case Block::CollisionType::kLeft:
        return std::string("kLeft"); break;
      case Block::CollisionType::kRight:
        return std::string("kRight"); break;
    };
  };

  // Detect collision between ball and borders
  DetectCollisionBorder(ball);

  // Detect collision between ball and racket
  Block::CollisionType collision_type;
  if (collision_previous != Game::CollisionObject::kRacket) {
    if (racket.DetectCollision(ball, collision_type)) {
      if (collision_type == Block::CollisionType::kTop) {
        // Compute normalized x-position of collision relative to racket center
        // -1.0 ... ball hits racket at the left corner
        //  0.0 ... ball hits racket at center
        //  1.0 ... ball hits racket at the right corner
        int racket_x_center = racket.get_x()+racket.get_w()/2;
        int ball_x_center = ball.get_x()+ball.get_w()/2;
        float x_pos_coll_norm = static_cast<float>(ball_x_center-racket_x_center)/(racket.get_w()/2);

        collision_previous = Game::CollisionObject::kRacket;
        ball.ChangeDirection(collision_type, x_pos_coll_norm*k_deflection_angle_max);
      }
    }
  }


  // Detect collision between ball and bricks 
  
  // Sort possible multiple collisions by overlap
  std::multimap<int, Block::CollisionType, std::greater<int>> sorted_map;
  for (auto &brick : wall.bricks) {
    if (brick.get_exists()) {
      int overlap;
      if (brick.DetectCollision(ball, collision_type, &overlap)) {
        
        sorted_map.insert(std::make_pair(overlap, collision_type));
        brick.set_exists(false);
        score += brick.get_value();
      }
    }
  }
  
  if (!sorted_map.empty()) {
    collision_previous = Game::CollisionObject::kBrick;
    ball.ChangeDirection(sorted_map.begin()->second);
  }
}

void Game::DetectCollisionBorder(Ball &ball) {
  int x = ball.get_x();
  int y = ball.get_y();
  float v_x = ball.get_velocity_x();
  float v_y = ball.get_velocity_y();
  
  if (x <= 0 && collision_previous != Game::CollisionObject::kBorderLeft) {
    collision_previous = Game::CollisionObject::kBorderLeft;
    ball.set_velocity(-v_x, v_y);
    // std::cout << "collision left\n";
    // std::cout << "ball.x = " << x << std::endl;
    // std::cout << "ball.y = " << y << std::endl;
  } else if (x >= static_cast<int>(kScreenWidth)-ball.get_w() && collision_previous != Game::CollisionObject::kBorderRight) {
    collision_previous = Game::CollisionObject::kBorderRight;
    ball.set_velocity(-v_x, v_y);
    // std::cout << "collision right\n";
    // std::cout << "ball.x = " << x << std::endl;
    // std::cout << "ball.y = " << y << std::endl;
  } else if (y <= 0 && collision_previous != Game::CollisionObject::kBorderTop) {
    collision_previous = Game::CollisionObject::kBorderTop;
    ball.set_velocity(v_x, -v_y);
    // std::cout << "collision top\n";
    // std::cout << "ball.x = " << x << std::endl;
    // std::cout << "ball.y = " << y << std::endl;
  } else if (y > static_cast<int>(kScreenHeight)) {
    collision_previous = Game::CollisionObject::kBorderBottom;
    // std::cout << "collision bottom\n";
    // std::cout << "ball.x = " << x << std::endl;
    // std::cout << "ball.y = " << y << std::endl;
    BallLost();
  } 
}

void Game::BallLost() {
  
  lives_count--;
  ball.set_released(false);
  ball.set_x(racket.get_x()+k_racket_width/2-k_ball_width/2);
  ball.set_y(racket.get_y()-k_ball_width);
  ball.set_velocity(0.0, 0.0);
  collision_previous = Game::CollisionObject::kRacket;

  std::cout << "Ball lost.\n";
  std::cout << "Lives left: " << lives_count << "\n\n";

}


int Game::get_score() const { 
  return score; 
}
