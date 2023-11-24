#include "hud.hpp"
#include <iostream>


Hud::Hud(int hudposx, int hudposy){
    hudPosX = hudposx;
    hudPosY = hudposy;
}

void Hud::drawInfo(Renderer& r, int level){
    std::string sLevel = std::to_string(level);
    char const *cLevel = sLevel.c_str(); 

    r.draw_text(cLevel, hudPosX, hudPosY);

}
