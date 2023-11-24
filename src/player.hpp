#ifndef PLAYER
#define PLAYER

#include <list>
#include <string>
#include <SDL2/SDL.h>
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
    void setAttack(InputState);
    float getAttackDirection();
    void gainXP(int);

    Weapon weapon_;
    SDL_Texture *texture_front_;
    SDL_Texture *texture_right_;
    SDL_Texture *texture_left_;

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
    float attack_direction_;

};


#endif
