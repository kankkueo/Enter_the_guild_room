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

    Game();
    void movePlayer(InputState&);
    void spawnProjectile(int, int, int, int, int, float, SDL_Texture*);
    //! All projectiles move. Deal damage to entities that are hit
    void moveProjectiles(Renderer&);
    //! All monsters move according to their movement pattern
    void moveMonsters(Renderer&);
    void parseInput(Renderer&);
    //! A standard game cycle
    int tick(Renderer&);
    //! Renders the game
    void render(Renderer&);
    //! Creates a new room
    void changeRoom(Renderer&);
    //! Calculates camera offset
    void calcOffset(Renderer&);
    //! Scans nearby objects to display in info text
    void scanNear(Renderer&);
    void menuTick(Renderer&);
    void menuRender(Renderer&);
    //! Checks if weapons are nearby to pick up
    Weapon* scanWeapons(Renderer&);
    //! Checks if potions are nearby to pick up
    HealingPotion* scanPotions(Renderer&);


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

};


#endif


