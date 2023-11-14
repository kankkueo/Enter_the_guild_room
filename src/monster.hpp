#include "game.hpp"

class Monster: public Entity {
public:
    Monster(int hp, int dmg);

    int GetHP();
    int GetDMG();
    void TakeDMG(int value);

private:
    bool alive_;
    int hp_;
    int dmg_;

};