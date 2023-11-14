#include "renderer.hpp"
#include "game.hpp"

#include <iostream>

int main() {

    Game game = Game();
    Renderer rend = Renderer(1920, 1080, SDL_RENDERER_ACCELERATED, 0);
    rend.initSDL();

    game.player_.texture_ = rend.loadTexture("./assets/dude.png");

    Room startroom = Room("Startroom", 720, 480, rend.loadTexture("./assets/startroom.png"));
    game.room_ = &startroom;
    

    while (game.tick()) {
        rend.prepareScene(*game.room_);
        rend.drawTexture(game.player_.texture_, game.player_.x_, game.player_.y_);
        rend.presentScene();
        SDL_Delay(10);
    }


    rend.destroy();

}

