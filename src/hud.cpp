#include "hud.hpp"
#include <iostream>



Hud::Hud(int hudposx, int hudposy){
    hudPosX = hudposx;
    hudPosY = hudposy;
}

void Hud::drawInfo(Renderer& r, int level, int health){
    std::string sLevel = std::to_string(level);
    char lvText[] = "Level: ";
    char const *cLevel = strcat(lvText, sLevel.c_str()); 
    

    r.draw_text(cLevel, hudPosX, hudPosY, 0);

    std::string sHealth = std::to_string(health);
    char hpText[] = "HP: ";
    char const *cHealth = strcat(hpText, sLevel.c_str()); 

    r.draw_text(cHealth, hudPosX, hudPosY + 25, 0);

}
