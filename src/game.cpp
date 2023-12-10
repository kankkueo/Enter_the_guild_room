#include "game.hpp"
#include "entity.hpp"
#include "input.hpp"
#include "room.hpp"
#include "weapon.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <list>


Game::Game(): 
    input_(Input()), 
    player_(Player("test geezer", 100, 100)),
    hud_(Hud(100,100))
{
    running_ = true;
    x_offset_ = 0;
    y_offset_ = 0;
    room_templates_ = std::list<Room>();
    projectiles_ = std::list<Projectile>();
    infoText = " ";
    game_level_ = 1;
    paused_ = false;
    mob_attack_delay_ = 120;
}

void Game::parseInput(Renderer& r) {

    // scans the inputs into inputState
    if (input_.scan()) {
        running_ = false;
        return;
    }
    
    // fetches inputState
    InputState s = input_.getState();

    movePlayer(s);
    
    /*if (s.menu) {
        running_ = false;
    }*/

    if (s.interact) {

        Coordinate ppos = player_.center();

        Weapon* w = scanWeapons(r);
        if (w) {
            player_.weapon_->x_ = ppos.x;
            player_.weapon_->y_ = ppos.y;
            room_->weapons_.push_back(player_.weapon_);
            player_.weapon_ = w;
            w->projectile_texture_ = r.loadTexture("./assets/entities/player-bullet.png");
        }

        HealingPotion* i = scanPotions(r);
        if(i) {
            player_.Heal(i->getHealing());
        }

        Coordinate rpos;
        rpos.x = room_->advanceDoorX_;
        rpos.y = room_->advanceDoorY_;

        if(ppos.x > rpos.x - 64 && ppos.x < rpos.x + 64 && ppos.y > rpos.y - 64 && ppos.y < rpos.y + 64 && room_->monsters_.empty()){
            
            changeRoom(r);
        }
        input_.resetInteract();
    }

    if (s.attack || s.attackUp || s.attackDown || s.attackLeft || s.attackRight) {
        if (player_.attack(s, projectiles_)) {
            r.playSound(player_.weapon_->sound_, 0);
        }
    }

    if(s.menu){
        input_.resetInput();
        paused_ = true;
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

void Game::changeRoom(Renderer& r) {
    input_.resetInput();
    delete room_;
    game_level_++;
    mob_attack_delay_ = 180;
    //player_.healMax();
    if (game_level_ == 20) {
        room_ = genBossRoom(r, game_level_);
    }
    else if (game_level_ == 21) {
        infoText = "You won!";
        running_ = false;
    }
    else {
        room_ = genRoom(r, game_level_);
    }
}

void Game::movePlayer(InputState& s) {
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

void Game::moveProjectiles(Renderer& r) {
    for (auto p = projectiles_.begin(); p != projectiles_.end(); p++) {
        p->move();

        for (auto m = room_->monsters_.begin(); m != room_->monsters_.end(); m++) {
            if (p->collidesWith(**m) && p->damage_monsters_) {
                (*m)->TakeDMG(p->dmg_);
                p = projectiles_.erase(p);
                
                if (!(*m)->isAlive()) {
                    (*m)->dropWeapon(room_->weapons_);
                    (*m)->dropPotion(room_->potions_);
                    r.playSound((*m)->sounds_.death_, 2);
                    delete *m;
                    m = room_->monsters_.erase(m);
                    if (player_.gainXP(300)) {
                        r.playSound(player_.sounds_.taunt_, 3);
                    }
                }
                else {
                    r.playSound((*m)->sounds_.hit_, 4);
                }

                break;
            }
        }

        if (p->collidesWith(player_) && !p->damage_monsters_) {
            player_.TakeDMG(p->dmg_);
            r.playSound(player_.sounds_.hit_, 3);
        }

        if (p->x_ > room_->width_ || p->x_ < 0 || p->y_ > room_->height_ || p->y_ < 0) {
            p = projectiles_.erase(p);
        }
    }
}

void Game::moveMonsters(Renderer& r) {
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

        if (mob_attack_delay_ <= 0) {
            if ((*m)->attack(player_, projectiles_)) {
                r.playSound((*m)->getAttackSound(), 5 + rand() % 2);
            }
        }
        else {
            mob_attack_delay_--;
        }

        // mobs make random taunt sounds
        if (rand() % 2000 == 1) {
            r.playSound((*m)->sounds_.taunt_, 3);
        }

    }
}

// Main game cycle
int Game::tick(Renderer& r) {

    if (player_.shoot_ticks_ > 0) {
        player_.shoot_ticks_--;
    }

    scanNear(r);

    parseInput(r);

    moveProjectiles(r);
    
    moveMonsters(r);

    calcOffset(r);

    if (!player_.isAlive()) {
        infoText = "YOU DIED";
        running_ = false;
        r.playSound(player_.sounds_.death_, 4);
    }

    return 0;
}

void Game::menuTick(Renderer& r){
    InputState s = input_.getState();
    if(s.menu){
        s.menu = false;
        paused_ = false;
        std::cout << "DD" << std::endl; //ei mee tänne???
    }
    //std::cout << "ASD" << std::endl; menee tänne!!!
}

void Game::menuRender(Renderer& r){

}


Weapon* Game::scanWeapons(Renderer& r) {
    Coordinate ppos = player_.center();

    for (auto w = room_->weapons_.begin(); w != room_->weapons_.end(); w++) {
        int x_diff = (*w)->x_ - ppos.x;
        int y_diff = (*w)->y_ - ppos.y;
        if (x_diff * x_diff + y_diff * y_diff <= 100 * 100) {
            room_->weapons_.erase(w);
            return *w;
        }
    }
    return NULL;
}

HealingPotion* Game::scanPotions(Renderer& r) {
    Coordinate ppos = player_.center();

    for (auto w = room_->potions_.begin(); w != room_->potions_.end(); w++) {
        int x_diff = (*w)->x_ - ppos.x;
        int y_diff = (*w)->y_ - ppos.y;
        if (x_diff * x_diff + y_diff * y_diff <= 100 * 100) {
            room_->potions_.erase(w);
            return *w;
        }
    }
    return NULL;
}

void Game::scanNear(Renderer& r) {
    Coordinate ppos = player_.center();
    Coordinate rpos;
    rpos.x = room_->advanceDoorX_;
    rpos.y = room_->advanceDoorY_;

    for (auto w = room_->weapons_.begin(); w != room_->weapons_.end(); w++) {
        int x_diff = (*w)->x_ - ppos.x;
        int y_diff = (*w)->y_ - ppos.y;
        if (x_diff * x_diff + y_diff * y_diff <= 100 * 100) {
            infoText = "Press E to swap weapon: " + (*w)->toString();
            displayWeapon_ = (*w);
            return;
        }
    }

    for (auto w = room_->potions_.begin(); w != room_->potions_.end(); w++) {
        int x_diff = (*w)->x_ - ppos.x;
        int y_diff = (*w)->y_ - ppos.y;
        if (x_diff * x_diff + y_diff * y_diff <= 100 * 100) {
            infoText = "Press E to use potion: " + (*w)->toString();
            return;
        }
    }

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

    for (HealingPotion* itm: room_->potions_) {
        r.drawTexture(itm->texture_, itm->x_ - x_offset_, itm->y_ - y_offset_, 0.0, SDL_FLIP_NONE);
    }

    for (Weapon* w: room_->weapons_) {
        r.drawTexture(w->texture_, w->x_ - x_offset_, w->y_ - y_offset_, 0.0, SDL_FLIP_NONE);
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
    
    hud_.drawInfo(r, player_.GetLevel(), player_.GetHP(), player_.getMaxHp(), game_level_);

    std::list<std::string> rows;
    std::string row = "";
    for(char& c : infoText){
        if(c == '\n' || c == '\0'){

            rows.push_back(row);
            row = "";
        }else{
            row += c;
        }
    }
    if(row.size() > 0){
        rows.push_back(row);
    }
    SDL_Color c = {255,255,255};
    int y = 0;
    std::string txt = "";
    for(std::list<std::string>::const_iterator i = rows.begin(); i != rows.end(); ++i){
        txt = (*i);
        if(y == 1){
            txt += "(";
            //Display dmgDiff
            if(displayWeapon_->getDmg() > player_.weapon_->getDmg()){
                c = {0,255,0};
                txt += "+";
            }else if(displayWeapon_->getDmg() < player_.weapon_->getDmg()){
                c = {255,0,0};
            }else{
                
            }
            txt += std::to_string(displayWeapon_->getDmg() - player_.weapon_->getDmg()) + ")";

        }else if(y == 2){
            txt += "(";
            //display firerateDiff
            if(displayWeapon_->getFirerate() > player_.weapon_->getFirerate()){
                c = {0,255,0};
                txt += "+";
            }else if(displayWeapon_->getFirerate() < player_.weapon_->getFirerate()){
                c = {255,0,0};
            }else{
            
            }
            txt += std::to_string(displayWeapon_->getFirerate() - player_.weapon_->getFirerate()) + ")";
        }

        //draw info on weapon to be picked up
        r.draw_text(txt.c_str(), r.getWinWidth()/2, 100+(22*y), c);
        y++;
    }
    

}

