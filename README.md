# Game name

This is a rogue-like dungeon crawler top-down shooter written in c++.
In the game, the player has to get through a set of randomized rooms with increasingly difficult random monsters with random weapons until they reach the final boss.
Defeating the boss ends the game.
The game is reset upon player death.


## Build instructions

#### Prerequisites

Compiling the project requires gcc and make.

The following libraries also to be installed
on your system:

- sdl2
- sdl2_image
- sdl2_ttf
- sdl2_mixer

These can be installed by running  
`sudo apt install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-ttf-2.0-0 libsdl2-mixer-2.0-0`

#### Compiling

Run `make` in the project root.  
`make run` starts the game.

## Playing the game

After `make run` the game starts instantly. The game quits when the player either dies or completes the game.

#### Controls

- WASD keys: Move around
- Arrow keys: Shoot your weapon
- E: Interact with items (switch weapons, pick up healing potions, go to the next room)