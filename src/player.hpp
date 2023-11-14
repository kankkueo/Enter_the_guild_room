#include <list>
#include <string>
#include "entity.hpp"
#include "input.hpp"

class Player: public Entity {
public:
    Player(const std::string& name);

    const std::string GetName() const;
    int GetHP();
    int GetXP();
    int GetDMG();

    void Heal(int);
    void TakeDMG(int);
    void UpdateXP(int);
    void UpdateDMG(int);
    void setMove(InputState);

private:
    bool alive_;
    std::string name_;
    int hp_;
    int dmg_;
    int xp_;
    std::list<std::string> inventory_;      // string should be changed to Item when there is a class for it

};
