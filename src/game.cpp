#include "game.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include <iostream>

Game::Game() {
    input_ = Input();
    entity1_ = Entity();

    running_ = true;
}

int Game::playerMove(InputState s) {

    if (s.up && s.right) {
        entity1_.direction_ = 0.7853982;
    }
    else if (s.up && s.left) {
        entity1_.direction_ = 2.3561945;
    }
    else if (s.down && s.right) {
        entity1_.direction_ = 5.4977871;
    }
    else if (s.down && s.left) {
        entity1_.direction_ = 3.9269908;
    }
    else if (s.up) {
        entity1_.direction_ = 1.5707963;
    }
    else if (s.down) {
        entity1_.direction_ = 4.7123890;
    }
    else if (s.left) {
        entity1_.direction_ = 3.1415927;
    }
    else if (s.right) {
        entity1_.direction_ = 0;
    }
    else {
        return 0;
    }

    entity1_.move();
    return 1;
}

void Game::parseInput() {

    input_.scan();
    
    InputState s = input_.getState();
    playerMove(s);

    if (s.menu) {
        running_ = false;
    }
}

int Game::tick() {

    if (running_) {
        parseInput();

    } else {
        return 0;
    }

    return 1;
}
