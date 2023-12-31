#ifndef MONSTER
#define MONSTER

#include "entity.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "weapon.hpp"
#include "consumables.hpp"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <string>

/*!
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
    Item* item_;

    virtual void setMove(Player&);
    virtual bool attack(Player&, std::list<Projectile>&);
    virtual void dropWeapon(std::list<Weapon*>&);
    virtual void dropPotion(std::list<HealingPotion*>&);
    virtual Mix_Chunk* getAttackSound();

    SoundSet sounds_;

protected:
    bool alive_;
    int hp_;
    int dmg_;
    int max_speed_;
    std::string name_;

};

/*! 
 *  Basic melee monster
 * 
 *  - Moves towards the player
 *  - Deals melee damage when close
 */ 

class MeleeMob: public Monster {

public:
    MeleeMob(int, int, int, int, int, HealingPotion*);

    bool attack(Player&, std::list<Projectile>&);
    void setMove(Player&);
    void dropPotion(std::list<HealingPotion*>&);

    HealingPotion* potion_;
    int attack_ticks_;
    int attack_cooldown_;
};


/*! 
 *  Basic ranged monster
 * 
 *  - Tries to keep at optimal_distance_ from the player
 *  - Deals ranged damage
 */ 

class RangedMob: public Monster {

public:
    RangedMob(int, int, int, int, int, Weapon*);

    bool attack(Player&, std::list<Projectile>&);
    void setMove(Player&);
    void dropWeapon(std::list<Weapon*>&);
    Mix_Chunk* getAttackSound();

    Weapon* weapon_;
    int attack_ticks_;
    int optimal_distance_; 

};

/*!
 *  Final boss
 *
 *  - Combines melee and ranged attack patterns
 */

class Boss: public Monster {
    
public:
    Boss(int);

    bool attack(Player&, std::list<Projectile>&);
    void setMove(Player&);
    Mix_Chunk* getAttackSound();

    // attack pattern 0 = melee, 1 = ranged
    int attack_pattern_;
    Weapon* weapon_;
    int attack_ticks_;
    int attack_cooldown_;
    int optimal_distance_; 

};

//! enum for randomizing mobs
enum MonsterType {
    MeleeMobType,
    RangedMobType
};

//! Generate a random monster baseed on level
Monster* genRandomMob(Renderer&, int, int, int);

#endif

