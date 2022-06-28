#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "defines.h"
#include "misc.h"

// Geometry
constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
constexpr std::size_t k_infobar_height{60};

// Racket
constexpr std::size_t k_racket_width {100};
constexpr std::size_t k_racket_height {20};

// Ball
constexpr std::size_t k_ball_width {20};

// Brick
constexpr std::size_t k_brick_width {60};
constexpr std::size_t k_brick_height {25};

// Brick wall
constexpr std::size_t k_brick_wall_rows {8};
constexpr std::size_t k_brick_wall_cols {8};
constexpr std::size_t k_brick_gap {2};
constexpr std::size_t k_brick_value {100};

// Screen
constexpr std::size_t kScreenWidth = (k_brick_width+k_brick_gap)*k_brick_wall_cols + k_brick_gap;
constexpr std::size_t kScreenHeight = kScreenWidth;

// Colors
constexpr Color k_color_brick(0x00, 0x99, 0x99, 0xFF);
//constexpr Color k_color_brick(0x00, 0x40, 0xFF, 0xFF);

constexpr Color k_color_racket(0xE0, 0xE0, 0xE0, 0xFF);

constexpr Color k_color_ball(0x66, 0xCC, 0x00, 0xFF);

// Controlls
constexpr int k_pad_position_increment = 10;
constexpr float k_init_v_x = 1.0;
constexpr float k_init_v_y = -5.0;
constexpr float k_mouse_vel_factor = 8.0;
constexpr float k_ball_v_x_max = 4.0;
constexpr float k_deflection_angle_max = 20.0; //deg

// Game exit
constexpr int k_exit_game_delay = 3000; //ms

#endif // CONSTANTS_H