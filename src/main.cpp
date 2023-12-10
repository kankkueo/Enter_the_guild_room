#include "renderer.hpp"
#include "game.hpp"
#include "weapon.hpp"

#include <iostream>
#include <list>

int main() {

    srand (time(NULL));

    Game game = Game();
    Renderer rend = Renderer(1920, 1080, SDL_RENDERER_ACCELERATED, 0);
    rend.initSDL();

    game.player_.texture_front_ = rend.loadTexture("./assets/entities/teekkari1-front.png");
    game.player_.texture_left_= rend.loadTexture("./assets/entities/teekkari1-left.png");
    game.player_.texture_right_= rend.loadTexture("./assets/entities/teekkari1-right.png");

    game.player_.sounds_.taunt_ = rend.loadSound("");
    game.player_.sounds_.death_ = rend.loadSound("");
    game.player_.sounds_.hit_ = rend.loadSound("");

    
    std::cout << "Starting game" << std::endl;
    game.paused_ = true;
    while (game.running_) {
        if(!game.paused_){
            game.tick(rend);
            rend.prepareScene();
            game.render(rend);
            rend.presentScene();
            SDL_Delay(1000/60);
        }else{
            game.menuTick(rend);
            rend.prepareScene();
            game.menuRender(rend);
            rend.presentScene();
            SDL_Delay(1000/60);
        }
    }

    SDL_Delay(2000);
    rend.destroy();

}

