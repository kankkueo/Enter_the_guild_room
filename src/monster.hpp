#ifndef MONSTER
#define MONSTER

#include "entity.hpp"
#include "player.hpp"

/*
 * Base class for monster
 */

class Monster: public Entity {
public:
    Monster(int, int, int, int, int, int, int);
    ~Monster();

    int GetHP();
    int GetDMG();
    void TakeDMG(int);
    bool isAlive();

    virtual void setMove(Player&);
    virtual void action(Player&);

protected:
    bool alive_;
    int hp_;
    int dmg_;
    int max_speed_;

};


/*  Basic melee monster
 * 
 *  - Moves towards the player
 *  - Deals melee damage when close
 */ 

class MeleeMob: public Monster {

public:
    MeleeMob(int, int, int, int, int, int, int);

    void action(Player&);
    void setMove(Player&);

};


/*  Basic ranged monster
 * 
 *  - Moves away from the player
 *  - Deals ranged damage
 */ 

class RangedMob: public Monster {

public:
    RangedMob(int, int, int, int, int, int, int);

    void action(Player&);
    void setMove(Player&);

};


#endif
