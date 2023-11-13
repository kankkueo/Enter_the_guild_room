#include "game.hpp"
#include "renderer.hpp"
#include "input.hpp"

Game::Game() {
    input_ = Input();
    entity1_ = Entity();

    running_ = true;
}

void Game::playerMove(InputState s) {

    if (s.up) {
        entity1_.y_ -= entity1_.speed_;
    }
    if (s.down) {
        entity1_.y_ += entity1_.speed_;
    }
    if (s.left) {
        entity1_.x_ -= entity1_.speed_;
    }
    if (s.right) {
        entity1_.x_ += entity1_.speed_;
    }
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
