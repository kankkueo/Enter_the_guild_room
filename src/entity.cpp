#include <math.h>
#include <iostream>
#include "entity.hpp"
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

Coordinate Entity::newPos() {
    return Coordinate {
        (int) (x_ + cos(direction_) * speed_),
        (int) (y_ - sin(direction_) * speed_)
    };
}

Coordinate Entity::center() {
    return Coordinate {
        (int) ((2 * x_ + size_x_)/2),
        (int) ((2 * y_ + size_y_)/2)
    };
}

Coordinate Entity::newCenter() {
    Coordinate c = newPos();
    return Coordinate {
        (int) ((2 * c.x + size_x_)/2),
        (int) ((2 * c.y + size_y_)/2)
    };
}
