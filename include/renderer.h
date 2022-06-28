#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include "SDL.h"

#include "brick.h"
#include "ball.h"
#include "brick_wall.h"
#include "racket.h"

class Renderer {
  private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  void RenderElement(Block &block);

  const std::size_t screen_width;
  const std::size_t screen_height;

  public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Racket &racket, Ball &ball, BrickWall &wall);
  void UpdateWindowTitle(int lives, int score, int fps);
  void UpdateWindowTitle(std::string label);

};

#endif