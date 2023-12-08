#ifndef MONSTER
#define MONSTER

#include "entity.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "weapon.hpp"
#include <SDL2/SDL_mixer.h>
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
    std::string getName();

    virtual void setMove(Player&);
    virtual bool attack(Player&, std::list<Projectile>&);
    virtual void dropItem(std::list<Weapon*>&);
    virtual Mix_Chunk* getAttackSound();

    SoundSet sounds_;

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

    bool attack(Player&, std::list<Projectile>&);
    void setMove(Player&);

    int attack_ticks_;
    int attack_cooldown_;
};


/*  Basic ranged monster
 * 
 *  - Tries to keep at optimal_distance_ from the player
 *  - Deals ranged damage
 */ 

class RangedMob: public Monster {

public:
    RangedMob(int, int, int, int, int, Weapon*);

    bool attack(Player&, std::list<Projectile>&);
    void setMove(Player&);
    void dropItem(std::list<Weapon*>&);
    Mix_Chunk* getAttackSound();

    Weapon* weapon_;
    int attack_ticks_;
    int optimal_distance_; 

};

/*
 *  Final boss
 */

class Boss: public Monster {
    
public:
    Boss(int);

    bool attack(Player&, std::list<Projectile>&);
    void setMove(Player&);

};

// enum for randomizing mobs
enum MonsterType {
    MeleeMobType,
    RangedMobType
};

Monster* genRandomMob(Renderer&, int, int, int);

#endif

