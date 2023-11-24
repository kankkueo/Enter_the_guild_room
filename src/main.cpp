#include "renderer.hpp"
#include "game.hpp"

#include <iostream>
#include <list>

int main() {

    srand (time(NULL));

    Game game = Game();
    Renderer rend = Renderer(1920, 1080, SDL_RENDERER_ACCELERATED, 0);
    rend.initSDL();

    game.player_.texture_front_ = rend.loadTexture("./assets/teekkari1-front.png");
    game.player_.texture_left_= rend.loadTexture("./assets/teekkari1-left.png");
    game.player_.texture_right_= rend.loadTexture("./assets/teekkari1-right.png");

    game.player_.weapon_.texture_ = rend.loadTexture("./assets/gun1.png");
    game.player_.weapon_.projectile_texture_ = rend.loadTexture("./assets/projectile1.png");

    Room startroom = Room("Startroom", 720, 480, rend.loadTexture("./assets/startroom.png"), rend.loadTexture("./assets/trapdoor.png"));
    Room bigroom = Room("Big room", 2500, 1500, rend.loadTexture("./assets/bigroom1.png"), rend.loadTexture("./assets/trapdoor.png"));
    game.room1_ = &startroom;
    
    game.room_ = &bigroom;

    bigroom.addMonster();
    for(auto it = bigroom.monsters_.begin(); it != bigroom.monsters_.end(); it++) {
        it->texture_ = rend.loadTexture("./assets/Koneteekkari.png");
    }
    
    std::cout << "Starting game" << std::endl;

    while (game.running_) {
        
        game.tick(rend);
        rend.prepareScene();
        game.render(rend);
        rend.presentScene();
        SDL_Delay(1000/60);
    }


    rend.destroy();

}

