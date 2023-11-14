#include "renderer.hpp"
#include "game.hpp"

#include <iostream>

int main() {

    Game game = Game();
    Renderer rend = Renderer();
    rend.initSDL();

    game.player_.texture_ = rend.loadTexture("./assets/dude.png");

    while (game.tick()) {
        rend.prepareScene();
        rend.drawTexture(game.player_.texture_, game.player_.x_, game.player_.y_);
        rend.presentScene();
        SDL_Delay(10);
    }


    rend.destroy();

}

