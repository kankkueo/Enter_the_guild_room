#include "hud.hpp"
#include <iostream>
#include <string>



Hud::Hud(int hudposx, int hudposy){
    hudPosX = hudposx;
    hudPosY = hudposy;
}

void Hud::drawInfo(Renderer& r, int level, int health, int maxHp, int room){
    //display level
    std::string sLevel = std::to_string(level);
    char lvText[50] = "Level: ";
    strcat(lvText, sLevel.c_str()); 
    
    r.draw_text(lvText, hudPosX, hudPosY);

    //display health
    std::string sHealth = std::to_string(health) + "/" + std::to_string(maxHp);
    char hpText[50] = "HP: ";
    strcat(hpText, sHealth.c_str());
    
    SDL_Color c = {255,255,255};
    if(health < maxHp/5){
        c = {255,0,0};
    }
    r.draw_text(hpText, hudPosX, hudPosY + 25, c);

    //display room
    std::string sRoom = std::to_string(room);
    char roomText[50] = "Room: ";
    strcat(roomText, sRoom.c_str()); 

    r.draw_text(roomText, hudPosX+r.getWinWidth()-200, hudPosY);

}
