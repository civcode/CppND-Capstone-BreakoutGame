#include "brick.h"

Brick::Brick(int x, int y, int w, int h, Color color, int value) 
	: Block(x, y, w, h, color), value(value) { 
    exists = true; 
};

int Brick::get_value() {
    return value;
}

bool Brick::get_exists() {
    return exists;
}

void Brick::set_exists(bool exists) {
    this->exists = exists;
}