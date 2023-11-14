#include <math.h>
#include <iostream>
#include "game.hpp"

Entity::Entity(int x, int y, int size_x, int size_y) {
    x_ = x;
    y_ = y;
    size_x_ = size_x;
    size_y_ = size_y;
    speed_ = 0;
    direction_ = 0;
}

void Entity::move() {
    x_ += cos(direction_) * speed_;
    y_ -= sin(direction_) * speed_;
}

