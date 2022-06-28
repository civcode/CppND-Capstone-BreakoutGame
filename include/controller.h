#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "racket.h"

class Controller {
 private:
  bool is_game_running = false;
  bool is_first_loop = true;

  SDL_MouseMotionEvent mouse_motion_event;;
  
  void ChangePosition(Racket &racket, Ball &ball, Racket::Direction input);
  void ChangePosition(Racket &racket, Ball &ball, int mouse_x);
  void ReleaseBall(Ball &ball);

  public:
  void HandleInput(bool &running, Racket &racket, Ball &ball);
};

#endif