#ifndef HUD
#define HUD

#include "renderer.hpp"

class Hud{
public:
    Hud(int hudposx, int hudposy);
    void drawInfo(Renderer&, int level, int health);

private:
    int hudPosX;
    int hudPosY;

};







#endif