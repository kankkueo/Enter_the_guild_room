#include "hud.hpp"
#include <iostream>
#include <string>



Hud::Hud(int hudposx, int hudposy){
    hudPosX = hudposx;
    hudPosY = hudposy;
}

void Hud::drawInfo(Renderer& r, int level, int health){
    std::string sLevel = std::to_string(level);
    char lvText[50] = "Level: ";
    strcat(lvText, sLevel.c_str()); 
    

    r.draw_text(lvText, hudPosX, hudPosY);

    std::string sHealth = std::to_string(health);
    char hpText[50] = "HP: ";
    strcat(hpText, sHealth.c_str()); 

    r.draw_text(hpText, hudPosX, hudPosY + 25);

}
