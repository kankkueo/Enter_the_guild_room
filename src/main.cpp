#include "renderer.hpp"
#include "game.hpp"


int main() {


    Renderer rend = Renderer();
    Entity ent = Entity();

    rend.initSDL();


    ent.texture_ = rend.loadTexture("./assets/dude.png");


    int quit = 0;
    while (!quit) {

        rend.prepareScene();

        quit = doInput();
		
        rend.drawTexture(ent.texture_, 100, 100);
        rend.presentScene();


        SDL_Delay(10);
    }

    rend.destroy();


}

