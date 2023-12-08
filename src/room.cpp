#include <iostream>
#include "room.hpp"
#include "monster.hpp"
#include "weapon.hpp"

#define ROOM_TEMPLATES 7

RoomTemplate rt[ROOM_TEMPLATES] = {
    RoomTemplate {"Big room", "./assets/rooms/bigroom1.png", 2500, 1500, 4, 8},
    RoomTemplate {"Red room", "./assets/rooms/startroom.png", 720, 480, 1, 3},
    RoomTemplate {"Tile room1", "./assets/rooms/tileroom.PNG", 1920, 1080, 2, 6},
    RoomTemplate {"Tile room2", "./assets/rooms/tileroom2.PNG", 2560, 1440, 4, 8},
    RoomTemplate {"Tile room3", "./assets/rooms/tileroom3.PNG", 1603, 903, 3, 5},
    RoomTemplate {"Holy room", "./assets/rooms/holyroom.PNG", 1442, 811, 2, 4},
    RoomTemplate {"Freaky room", "./assets/rooms/freakyroom.PNG", 1366, 768, 2, 3},
};

Room::~Room() {
    //free(texture_);
    //free(advanceDoor_);

    for (auto itm = items_.begin(); itm != items_.end(); itm++) {
        itm = items_.erase(itm);
    }

    for (auto w = weapons_.begin(); w != weapons_.end(); w++) {
        w = weapons_.erase(w);
    }



}

Room::Room(const std::string& name, int width, int height, SDL_Texture *texture, SDL_Texture *advanceDoor)
    : name_(name), width_(width), height_(height), texture_(texture), advanceDoor_(advanceDoor) {
        monsters_ = std::list<Monster*>();
        items_ = std::list<Item*>();
        advanceDoorX_ = 75 + rand() % (width - 150);
        advanceDoorY_ = 75 + rand() % (height - 150);
}

void Room::addRandomMonsters(Renderer& r, int level, int amount) {
    for (int i = 0; i < amount; i++) {
        monsters_.push_back(genRandomMob(r, level, width_, height_));
    }
}

Room* genRoom(Renderer& r, int level) {
    int n = rand() % ROOM_TEMPLATES;
    Room* rm = new Room(rt[n].name, rt[n].width, rt[n].height,
        r.loadTexture(rt[n].texture_location.c_str()), r.loadTexture("./assets/trapdoor.png"));

    int mobs = rt[n].mobs_min + rand() % (rt[n].mobs_max - rt[n].mobs_min);
    rm->addRandomMonsters(r, level, mobs);

    std::cout << "Generated room " << rm->name_;
    std::cout << " with " << mobs << " monsters" << std::endl;;

    return rm;
}

