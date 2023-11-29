#ifndef MONSTER
#define MONSTER

#include "entity.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "weapon.hpp"
#include <SDL2/SDL_render.h>
#include <string>

/*
 * Base class for monster
 */

class Monster: public Entity {
public:
    Monster(const std::string&, int, int, int, int, int, int, int);
    ~Monster();

    int GetHP();
    int GetDMG();
    void TakeDMG(int);
    bool isAlive();

    virtual void setMove(Player&);
    virtual void attack(Player&, std::list<Projectile>&);

protected:
    bool alive_;
    int hp_;
    int dmg_;
    int max_speed_;
    std::string name_;

};

/*  Basic melee monster
 * 
 *  - Moves towards the player
 *  - Deals melee damage when close
 */ 

class MeleeMob: public Monster {

public:
    MeleeMob(int, int, int, int, int);

    void attack(Player&, std::list<Projectile>&);
    void setMove(Player&);

};


/*  Basic ranged monster
 * 
 *  - Moves away from the player
 *  - Deals ranged damage
 */ 

class RangedMob: public Monster {

public:
    RangedMob(int, int, int, int, int, Weapon*);

    void attack(Player&, std::list<Projectile>&);
    void setMove(Player&);

    Weapon* weapon_;
    int attack_ticks_;

};

enum MonsterType {
    MeleeMobType,
    RangedMobType
};

Monster* genRandomMob(Renderer&, int, int, int);

#endif
