
#include <iostream>
#include <string>

#include "misc.h"
#include "renderer.h"

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Breakout Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Hardware Accelerated Renderer could not be created.\n";
    
    // Use software renderer as fallback
    std::cerr << "Using Software Renderer.\n\n";
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
    if (nullptr == sdl_renderer) {
      std::cerr << "Software Renderer could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::RenderElement(Block &block) {
  // Render Block
  SDL_Rect rect;
  Color color = block.get_color();
  SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.alpha);
  rect.x = block.get_x();
  rect.y = block.get_y();
  rect.w = block.get_w();
  rect.h = block.get_h();
  SDL_RenderFillRect(sdl_renderer, &rect);
}

void Renderer::Render(Racket &racket, Ball &ball, BrickWall &wall) {
  SDL_Rect block;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);

  SDL_RenderClear(sdl_renderer);
  
  // Render Racket
  RenderElement(racket);

  // Render Bricks
  for (auto &brick : wall.bricks) {
    if (brick.get_exists())
      RenderElement(brick);
  }

  // Render Ball
  RenderElement(ball);
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int lives, int score, int fps) {
  std::string title{"Balls: " + std::to_string(lives) + " Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::UpdateWindowTitle(std::string label) {
  SDL_SetWindowTitle(sdl_window, label.c_str());
}
