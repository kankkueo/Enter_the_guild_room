#ifndef MONSTER
#define MONSTER

#include "game.hpp"

class Monster: public Entity {
public:
    Monster(int, int, int, int, int, int, int);

    int GetHP();
    int GetDMG();
    void TakeDMG(int);

private:
    bool alive_;
    int hp_;
    int dmg_;
    int max_speed_;

};

#endif
