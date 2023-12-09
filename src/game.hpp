#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <list>
#include "entity.hpp"
#include "input.hpp"
#include "player.hpp"
#include "room.hpp"
#include "renderer.hpp"
#include "hud.hpp"

class Game {

public:
    std::list<Room> room_templates_;
    Room *room_;
    Room *room1_;
    bool running_;
    Input input_;
    int x_offset_;
    int y_offset_;
    std::string infoText;
    int game_level_;
    Hud hud_;
    Player player_;
    std::list<Projectile> projectiles_;
    Weapon* displayWeapon_;
    bool paused_;

    Game();
    void movePlayer(InputState&);
    void spawnProjectile(int, int, int, int, int, float, SDL_Texture*);
    void moveProjectiles(Renderer&);
    void moveMonsters(Renderer&);
    void parseInput(Renderer&);
    int tick(Renderer&);
    void render(Renderer&);
    void calcOffset();
    void changeRoom(Renderer&);
    void calcOffset(Renderer&);
    void scanNear(Renderer&);
    void menuTick(Renderer&);
    void menuRender(Renderer&);
    Weapon* scanWeapons(Renderer&);
    Item* scanItems(Renderer&);


};


#endif


