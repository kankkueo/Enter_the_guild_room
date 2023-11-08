#include "renderer.hpp"

int main() {


    Renderer rend = Renderer();

    rend.initSDL();
    rend.prepareScene();
    rend.presentScene();


    SDL_Delay(1000);
    rend.destroy();

//    sdltest();

}

