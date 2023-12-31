#ifndef INPUT
#define INPUT

#include <SDL2/SDL.h>

typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool attack;
    bool interact;
    bool menu;
    bool attackUp;
    bool attackDown;
    bool attackLeft;
    bool attackRight;
    bool enter;
} InputState;

typedef struct {
    uint32_t up;
    uint32_t down;
    uint32_t left;
    uint32_t right;
    uint32_t attack;
    uint32_t interact;
    uint32_t menu;
    uint32_t attackUp;
    uint32_t attackDown;
    uint32_t attackLeft;
    uint32_t attackRight;
    uint32_t enter;
} InputMapping;


//! A class to hande inputs
class Input {
public:

    Input();
    int scan();
    void keyDown(SDL_KeyboardEvent*);
    void keyUp(SDL_KeyboardEvent*);
    void resetInput();
    void resetInteract();
    InputState getState();

private:

    InputState state_;
    InputMapping mapping_;

};

#endif
