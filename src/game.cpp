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
    rooms_ = std::list<Room>();
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

    if (s.interact) {
        //Coordinate ppos = player_.center();
        //Coordinate rpos;
        //rpos.x = room_->advanceDoorX_;
        //rpos.y = room_->advanceDoorY_;

        //if(ppos.x > rpos.x-64 && ppos.x < rpos.x + 64){
            
            changeRoom(room1_);
        //}
    }
}

void Game::calcOffset(Renderer& r) {
    // window size - padding
    int padding_x = 300;
    int padding_y = 300;
    int width = r.getWinWidth() - padding_x; 
    int height = r.getWinHeight() - padding_y;


    if ((player_.x_ >= width + x_offset_)) {
        x_offset_ = player_.x_ - width ;
    }
    else if ((player_.x_ <= padding_x + x_offset_)) {
        x_offset_ = player_.x_ - padding_x;
    }

    if ((player_.y_ >= height + y_offset_)) {
        y_offset_ = player_.y_ - height;
    }
    else if ((player_.y_ <= padding_y + y_offset_)) {
        y_offset_ = player_.y_ - padding_y;
    }
    
    
}



void Game::changeRoom(Room *r){
    //input_.resetInput();
    room_ = r;
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

}

int Game::tick(Renderer& r) {

    parseInput();
    
    calcOffset(r);

    return 0;
}

void Game::render(Renderer& r) {
    r.drawTexture(room_->texture_, -x_offset_, -y_offset_);
    r.drawTexture(room_->advanceDoor_, room_->advanceDoorX_-x_offset_, room_->advanceDoorY_-y_offset_);
    r.drawTexture(player_.texture_, 
        player_.x_ - x_offset_, 
        player_.y_ - y_offset_);

    for (Monster m: room_->monsters_) {
        r.drawTexture(m.texture_, m.x_ - x_offset_, m.y_ - y_offset_);
        std::cout << m.texture_ << std::endl; // for debugging
    }

}

