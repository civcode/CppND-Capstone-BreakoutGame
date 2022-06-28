#ifndef MISC_H
#define MISC_H

#include "defines.h"

class Color {
  public:
  uchar r, g, b, alpha;
  
  constexpr Color(uchar r, uchar g, uchar b, uchar alpha) : r(r), g(g), b(b), alpha(alpha) {}
  ~Color() = default;
};

#endif // MISC_H









