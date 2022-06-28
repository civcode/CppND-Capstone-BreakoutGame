#include <iostream>
#include <map>
#include <utility>

#include "block.h"

bool Block::DetectCollision(Block &other, CollisionType &collision_type, int *overlap) {
  int other_x = other.get_x();
  int other_y = other.get_y();
  int other_w = other.get_w();
  int other_h = other.get_h();
  
  // Compute overlap between blocks
  int overlap_top = 0;
  int overlap_bottom = 0;
  int overlap_left = 0;
  int overlap_right = 0;

  // Overlap top / bottop
  for (int xp=x; xp<x+w; xp++) {
    if(other.ContainsPoint(xp, y)) {
      overlap_top++;
      //std::cout << "overlap top detected" << overlap_top << std::endl;
    }
    if(other.ContainsPoint(xp, y+h)) {
      overlap_bottom++;
      //std::cout << "overlap bottom detected" << overlap_bottom << std::endl;;
    }
  }
  // Overlap left / right 
  for (int yp=y; yp<y+h; yp++) {
    if(other.ContainsPoint(x, yp)) {
      overlap_left++;
      //std::cout << "overlap top detected" << overlap_top << std::endl;
    }
    if(other.ContainsPoint(x+w, yp)) {
      overlap_right++;
      //std::cout << "overlap bottom detected" << overlap_bottom << std::endl;;
    }
  }
  
  // Sort collision types by overlap (decreasing order)
  std::multimap<int, Block::CollisionType, std::greater<int>> sorted_map;

  sorted_map.insert(std::make_pair(overlap_top, Block::CollisionType::kTop));
  sorted_map.insert(std::make_pair(overlap_bottom, Block::CollisionType::kBottom));
  sorted_map.insert(std::make_pair(overlap_left, Block::CollisionType::kLeft));
  sorted_map.insert(std::make_pair(overlap_right, Block::CollisionType::kRight));

  auto type2string = [](Block::CollisionType collision_type) { 
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

  if (overlap_top || overlap_bottom || overlap_left || overlap_right) {

    collision_type = sorted_map.begin()->second;

    // Handle optional float pointer argument
    if (overlap != nullptr) {
      *overlap = sorted_map.begin()->first;
    }

    return true;
  }

  return false;
}

bool Block::ContainsPoint(int x, int y) {
  return (x >= this->x && x < this->x+w && 
          y >= this->y && y < this->y+h);
}

int Block::get_x() const { 
  return x; 
}

int Block::get_y() const { 
  return y; 
}

int Block::get_w() const { 
  return w; 
}

int Block::get_h() const { 
  return h; 
}

Color Block::get_color() { 
  return color; 
}



