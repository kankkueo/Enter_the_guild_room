#include "renderer.hpp"
#include "game.hpp"

#include <iostream>

int main() {

    Game game = Game();
    Renderer rend = Renderer(1920, 1080, SDL_RENDERER_ACCELERATED, 0);
    rend.initSDL();

    game.player_.texture_ = rend.loadTexture("./assets/teekkari1.png");

    Room startroom = Room("Startroom", 720, 480, rend.loadTexture("./assets/startroom.png"));
    Room bigroom = Room("Big room", 2500, 2000, rend.loadTexture("./assets/bigroom1.png"));
    game.room_ = &startroom;
    

    while (game.running_) {
        game.tick();
        rend.prepareScene();
        game.render(rend);
        rend.presentScene();
        SDL_Delay(1000/60);
    }


    rend.destroy();

}

