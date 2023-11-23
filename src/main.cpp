#include "renderer.hpp"
#include "game.hpp"

#include <iostream>
#include <list>

int main() {

    Game game = Game();
    Renderer rend = Renderer(1920, 1080, SDL_RENDERER_ACCELERATED, 0);
    rend.initSDL();

    game.player_.texture_ = rend.loadTexture("./assets/teekkari1.png");

    Room startroom = Room("Startroom", 720, 480, rend.loadTexture("./assets/startroom.png"), rend.loadTexture("./assets/trapdoor.png"), 0, 0);
    Room bigroom = Room("Big room", 2500, 1500, rend.loadTexture("./assets/bigroom1.png"), rend.loadTexture("./assets/trapdoor.png"), 1250, 750);
    game.room1_ = &startroom;
    
    game.room_ = &bigroom;

    bigroom.addMonster();
    for(auto it = bigroom.monsters_.begin(); it != bigroom.monsters_.end(); it++) {
        it->texture_ = rend.loadTexture("./assets/Koneteekkari.png");
    }

    while (game.running_) {
        game.tick(rend);
        rend.prepareScene();
        game.render(rend);
        rend.presentScene();
        SDL_Delay(1000/60);
    }


    rend.destroy();

}

