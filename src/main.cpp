#include "renderer.hpp"
#include "game.hpp"


int main() {


    Renderer rend = Renderer();
    Entity ent = Entity();

    rend.initSDL();
    rend.prepareScene();


    ent.texture_ = rend.loadTexture("./assets/dude.png");
    rend.drawTexture(ent.texture_, 100, 100);
    rend.presentScene();

    SDL_Delay(1000);
    rend.destroy();

}

