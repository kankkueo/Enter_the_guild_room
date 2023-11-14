#include "game.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include <iostream>

Game::Game(): 
    input_(Input()), 
    player_(Player("test geezer", 100, 100)) {
    running_ = true;
}

void Game::parseInput() {

    input_.scan();
    
    InputState s = input_.getState();

    player_.setMove(s);
    
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

