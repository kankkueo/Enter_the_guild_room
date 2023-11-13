#include "renderer.hpp"
#include "game.hpp"

#include <iostream>

int main() {

    Game game = Game();
    Renderer rend = Renderer();
    rend.initSDL();

    game.entity1_.texture_ = rend.loadTexture("./assets/dude.png");

    while (game.tick()) {
        rend.prepareScene();
        rend.drawTexture(game.entity1_.texture_, game.entity1_.x_, game.entity1_.y_);
        rend.presentScene();
        SDL_Delay(10);
    }


    rend.destroy();

}

