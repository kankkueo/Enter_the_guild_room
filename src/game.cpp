#include "game.hpp"
#include "entity.hpp"
#include "input.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>


Game::Game(): 
    input_(Input()), 
    player_(Player("test geezer", 100, 100)),
    hud_(Hud(0,0))
{
    running_ = true;
    x_offset_ = 0;
    y_offset_ = 0;
    room_templates_ = std::list<Room>();
    projectiles_ = std::list<Entity>();
    infoText = " ";
}

void Game::parseInput() {

    // scans the inputs into inputState
    if (input_.scan()) {
        running_ = false;
        return;
    }
    
    // fetches inputState
    InputState s = input_.getState();

    movePlayer(s);
    
    if (s.menu) {
        running_ = false;
    }

    if (s.interact) {
        Coordinate ppos = player_.center();
        Coordinate rpos;
        rpos.x = room_->advanceDoorX_;
        rpos.y = room_->advanceDoorY_;

        if(ppos.x > rpos.x - 64 && ppos.x < rpos.x + 64 && ppos.y > rpos.y - 64 && ppos.y < rpos.y + 64 && room_->monsters_.empty()){
            
            changeRoom(room1_);
        }
    }

    if (s.attack || s.attackUp || s.attackDown || s.attackLeft || s.attackRight) {
        playerAttack(s);
    }
}

void Game::calcOffset(Renderer& r) {
    int padding_x = 800;
    int padding_y = 400;
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
    input_.resetInput();
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

void Game::playerAttack(InputState s) {
    if (player_.shoot_ticks_ <= 0) {
        player_.shoot_ticks_ = 60 / player_.weapon_->getFirerate();

        player_.setAttack(s);
        player_.weapon_->shoot(projectiles_, player_, player_.GetDMG(), player_.getAttackDirection());
    }
}

void Game::moveProjectiles() {
    for (auto p = projectiles_.begin(); p != projectiles_.end(); p++) {
        p->move();

        for (auto m = room_->monsters_.begin(); m != room_->monsters_.end(); m++) {
            if (p->collidesWith(**m)) {
                (*m)->TakeDMG(player_.weapon_->getDmg() + player_.GetDMG());
                p = projectiles_.erase(p);
                
                if (!(*m)->isAlive()) {
                    delete *m;
                    m = room_->monsters_.erase(m);
                }

                break;
            }
        }

        if (p->x_ > room_->width_ || p->x_ < 0 || p->y_ > room_->height_ || p->y_ < 0) {
            p = projectiles_.erase(p);
        }
    }
}

void Game::moveMonsters() {
    for (auto m = room_->monsters_.begin(); m != room_->monsters_.end(); m++) {
        (*m)->setMove(player_);
        
        Coordinate c = (*m)->newPos();

        if (c.x <= 0) {
            (*m)->x_ = 0;
        }
        else if (c.x + (*m)->size_x_ >= room_->width_) {
            (*m)->x_ = room_->width_ - (*m)->size_x_;
        }
        else {
            (*m)->x_ = c.x;
        }

        if (c.y <= 0) {
            (*m)->y_ = 0;
        }
        else if (c.y + (*m)->size_y_ >= room_->height_) {
            (*m)->y_ = room_->height_ - (*m)->size_y_;
        }
        else {
            (*m)->y_ = c.y;
        }
    }
}

// Main game cycle
int Game::tick(Renderer& r) {

    if (player_.shoot_ticks_ > 0) {
        player_.shoot_ticks_--;
    }

    scanNear(r);

    parseInput();

    moveProjectiles();
    
    moveMonsters();

    calcOffset(r);

    return 0;
}

void Game::scanNear(Renderer& r){
    Coordinate ppos = player_.center();
    Coordinate rpos;
    rpos.x = room_->advanceDoorX_;
    rpos.y = room_->advanceDoorY_;

    if (ppos.x > rpos.x - 64 && ppos.x < rpos.x + 64 && ppos.y > rpos.y - 64 && ppos.y < rpos.y + 64 && room_->monsters_.empty()) {
        infoText = "Press E to advance";
    } else {
        infoText = " ";
    }
}

void Game::render(Renderer& r) {
    r.drawTexture(room_->texture_, -x_offset_, -y_offset_, 0.0, SDL_FLIP_NONE);
    r.drawTexture(room_->advanceDoor_, room_->advanceDoorX_-x_offset_, room_->advanceDoorY_-y_offset_, 0.0, SDL_FLIP_NONE);

    for (Monster* m: room_->monsters_) {
        r.drawTexture(m->texture_, m->x_ - x_offset_, m->y_ - y_offset_, 0.0, SDL_FLIP_NONE);
    }

    InputState state = input_.getState();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Texture* player_texture;
    int weapon_xpos, weapon_ypos;

    double angle = -(player_.getAttackDirection() / 3.1415927 * 180);
    if (angle < -90 && angle > -270) {
        flip = SDL_FLIP_HORIZONTAL;
        angle -= 180;
    }

    if(state.left) {
        player_texture = player_.texture_left_;
        weapon_xpos = -15;
        weapon_ypos = 60;
    }
    else if(state.right) {
        player_texture = player_.texture_right_;
        weapon_xpos = 62;
        weapon_ypos = 74;
    }
    else if(state.up || state.down) {
        player_texture = player_.texture_front_;
        weapon_xpos = 37;
        weapon_ypos = 77;
    }
    else {
        player_texture = player_.texture_front_;
        weapon_xpos = 37;
        weapon_ypos = 77;
    }

     r.drawTexture(player_texture, 
        player_.x_ - x_offset_, 
        player_.y_ - y_offset_, 0.0, SDL_FLIP_NONE);
    
    r.drawTexture(player_.weapon_->texture_, 
        player_.x_ - x_offset_ + weapon_xpos,
        player_.y_ - y_offset_ + weapon_ypos,
        angle, flip);

    for (Entity e: projectiles_) {
        angle = -(e.direction_ / 3.1415927 * 180);
        r.drawTexture(e.texture_, e.x_ - x_offset_, e.y_ - y_offset_, angle, SDL_FLIP_NONE);
    }
    
    hud_.drawInfo(r, player_.GetLevel());

    r.draw_text(infoText.c_str(), r.getWinWidth()/2, 100);
    

}

