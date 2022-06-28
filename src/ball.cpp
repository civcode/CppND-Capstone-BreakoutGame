#include <cmath>
#include <Eigen/Dense>
#include <iostream>

#include "ball.h"

Ball::Ball(int x, int y, int w, int h, float velocity_x, float velocity_y, Color color) 
    : Block(x, y, w, h, color), 
    velocity_x(velocity_x), velocity_y(velocity_y), pos_x(x), pos_y(y) {
    released_count = 0; 
}

float Ball::get_pos_x() {
    return pos_x;
}
  
float Ball::get_pos_y() {
    return pos_y;
}

float Ball::get_velocity_x() { 
    return velocity_x; 
}

float Ball::get_velocity_y() { 
    return velocity_y; 
}

void Ball::set_x(int x) { 
    this->x = x; 
}

void Ball::set_y(int y) { 
    this->y = y; 
}

void Ball::set_velocity(float v_x, float v_y) { 
    velocity_x = v_x;
    velocity_y = v_y; 
}

void Ball::ChangeDirection(Block::CollisionType collision_type, float deflection) {
    // The collision type refers to the block the ball collides with
    // e.g. Block::CollisionType::kTop means that the other block is hit 
    // from the top by the ball

    // Rotation of the [vx, vy] velocity vector about the z-axis
    auto rotate = [this](float gamma) {
        gamma *= M_PI / 180.0;
        Eigen::Matrix3d rot_z;
        rot_z << cos(gamma), -sin(gamma), 0,
                 sin(gamma), cos(gamma), 0,
                 0, 0, 1;
        Eigen::Vector3d v;
        v << this->velocity_x, this->velocity_y, 0;
        v = rot_z * v;
        this->velocity_x = v[0];
        this->velocity_y = v[1];   
    };

    switch (collision_type) {
        case Block::CollisionType::kTop: 
        case Block::CollisionType::kBottom: {
            velocity_y *= (-1);
            break;
        } 
        case Block::CollisionType::kLeft: 
        case Block::CollisionType::kRight: {
            velocity_x *= (-1); 
            break;
        }    
    }

    if (deflection != 0) {
        rotate(deflection);
    }
}

void Ball::Update() {
    if (is_released) {
        pos_x += velocity_x;
        pos_y += velocity_y; 
        x = static_cast<int>(pos_x);
        y = static_cast<int>(pos_y);
    } else {
        pos_x = x;
        pos_y = y;
    }
}

void Ball::set_released(bool is_released) { 
    this->is_released = is_released; 
    if (is_released) {
        released_count++;
    }
}

bool Ball::get_released() { 
    return is_released; 
}

int Ball::get_released_count() {
    return released_count;
}



