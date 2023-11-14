#include "game.hpp"
#include "entity.hpp"
#include "input.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

Game::Game(): 
    input_(Input()), 
    player_(Player("test geezer", 100, 100))
{
    running_ = true;
    x_offset_ = 0;
    y_offset_ = 0;
}

void Game::parseInput() {

    if (input_.scan()) {
        running_ = false;
        return;
    }
    
    InputState s = input_.getState();

    movePlayer(s);
    
    if (s.menu) {
        running_ = false;
    }
}

void Game::calcOffset(Coordinate c) {
    if (player_.x_ >= 1920 - 400 + x_offset_) {
        x_offset_ += player_.speed_;
    }
    else if (player_.x_ <= 400 + x_offset_ && x_offset_ > 0) {
        x_offset_ -= player_.speed_;
    }

    if (player_.y_ >= 1080 - 400 + y_offset_) {
        y_offset_ += player_.speed_;
    }
    else if (player_.y_ <= 400 + y_offset_ && y_offset_ > 0) {
        y_offset_ -= player_.speed_;
    }
 
    
}

void Game::movePlayer(InputState s) {
    player_.setMove(s);
    Coordinate c = player_.newPos();

    if (c.x <= 0) {
        player_.x_ = 0;
    }
    else if (c.x + player_.size_x_ >= room_->width_) {
        player_.x_ = room_->width_ - player_.size_x_;
    }
    else {
        player_.x_ = c.x;
    }

    if (c.y <= 0) {
        player_.y_ = 0;
    }
    else if (c.y + player_.size_y_ >= room_->height_) {
        player_.y_ = room_->height_ - player_.size_y_;
    }
    else {
        player_.y_ = c.y;
    }

    calcOffset(c);
}

int Game::tick() {

    parseInput();
    

    return 0;
}

void Game::render(Renderer& r) {
    r.drawTexture(room_->texture_, -x_offset_, -y_offset_);
    r.drawTexture(player_.texture_, 
        player_.x_ - x_offset_, 
        player_.y_ - y_offset_);


}

