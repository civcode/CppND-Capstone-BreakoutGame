#include <algorithm>
#include <iostream>


#include "SDL.h"
#include "constants.h"
#include "controller.h"

void Controller::ChangePosition(Racket &racket, Ball &ball, Racket::Direction input) {
  int x = racket.get_x();
  int w = racket.get_w();
  if (input == Racket::Direction::kLeft && x > 0) {
    racket.set_x(std::max(x-k_pad_position_increment,0));
  } else if (input == Racket::Direction::kRight && x < kScreenWidth-w) {
    racket.set_x(std::min(x+k_pad_position_increment,static_cast<int>(kScreenWidth)-w));
  }

  // Update ball position
  if (!is_game_running)  {
    ball.set_x(ball.get_x()+racket.get_x()-x);
  }
}

void Controller::ChangePosition(Racket &racket, Ball &ball, int mouse_x) {
  int x = racket.get_x();
  int w = racket.get_w();
  if (mouse_x < w/2) {
    racket.set_x(0);
  } else if (mouse_x > kScreenWidth-w/2) {
    racket.set_x(kScreenWidth-w);
  } else {
    racket.set_x(mouse_x-w/2);
  }

  // Update ball position
  if (!ball.get_released() /*!is_game_running*/)  {
    ball.set_x(ball.get_x()+racket.get_x()-x);

  }
}

void Controller::ReleaseBall(Ball &ball) {
  is_game_running = true;
  if (!ball.get_released()) {
    ball.set_released(true);
    // Compute velocities depending on mouse motion
    if (abs(mouse_motion_event.xrel) > 1) {
      float mouse_v_x = static_cast<float>(mouse_motion_event.xrel) / kMsPerFrame; // Pixel per ms
      float ball_v_x = mouse_v_x*k_mouse_vel_factor;
      if (fabs(ball_v_x) < k_ball_v_x_max) {
        ball.set_velocity(ball_v_x, k_init_v_y);
      } else {
        ball.set_velocity((ball_v_x/fabs(ball_v_x)) * k_ball_v_x_max, k_init_v_y);
      } 
    } else {
      ball.set_velocity(0.0, k_init_v_y);
    }
    
  }
}

void Controller::HandleInput(bool &sdl_quit, Racket &racket, Ball &ball)  {
  // is_first_loop = true;
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      sdl_quit = true;
    } else if (e.type == SDL_KEYDOWN) {
      // switch (e.key.keysym.sym) {
      //   case SDLK_UP:
      //     //ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
      //     break;

      //   case SDLK_DOWN:
      //     //ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
      //     break;

      //   case SDLK_LEFT:
      //     ChangePosition(racket, ball, Racket::Direction::kLeft);
      //     //ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
      //     break;

      //   case SDLK_RIGHT:
      //     ChangePosition(racket, ball, Racket::Direction::kRight);
      //     //ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
      //     break;

      //   case SDLK_SPACE:
      //     ReleaseBall(ball);
      // }
    } else if (e.type == SDL_MOUSEMOTION) {
      mouse_motion_event = e.motion;
      if (is_first_loop) {
        mouse_motion_event.xrel = 0;
        is_first_loop = false;
      }
      ChangePosition(racket, ball, e.motion.x);

    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      SDL_PumpEvents();
      if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        ReleaseBall(ball);
      }
    }
  }
  
}