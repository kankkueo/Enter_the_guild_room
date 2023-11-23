#ifndef PLAYER
#define PLAYER

#include <list>
#include <string>
#include "entity.hpp"
#include "input.hpp"
#include "weapon.hpp"

class Player: public Entity {
public:
    Player(const std::string&, int, int);

    const std::string GetName() const;
    int GetHP();
    int GetXP();
    int GetDMG();
    int GetMaxSpeed();
    int GetLevel();

    void Heal(int);
    void TakeDMG(int);
    void UpdateXP(int);
    void UpdateDMG(int);
    void setMove(InputState);
    void gainXP(int);

    Weapon weapon_;

private:
    bool alive_;
    std::string name_;
    int hp_;
    int dmg_;
    int xp_;
    int max_speed_;
    std::list<std::string> inventory_;      // string should be changed to Item when there is a class for it
    int level_;
    int xp_to_Level_up_;

};


#endif
