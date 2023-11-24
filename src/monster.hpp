#ifndef MONSTER
#define MONSTER

#include "entity.hpp"
#include "player.hpp"

class Monster: public Entity {
public:
    Monster(int, int, int, int, int, int, int);

    int GetHP();
    int GetDMG();
    void TakeDMG(int);
    bool isAlive();

    void setMove(Player&);

protected:
    bool alive_;
    int hp_;
    int dmg_;
    int max_speed_;

};

/*
class MeleeMob: public Monster {

public:
    MeleeMob(int, int, int, int, int, int, int);

    void action(Player&);


};
*/

#endif
