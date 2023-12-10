#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include "input.hpp"

Input::Input() {
    state_.up = false;
    state_.down = false;
    state_.left = false;
    state_.right = false;
    state_.attack = false;
    state_.interact = false;
    state_.menu = false;
    state_.attackUp = false;
    state_.attackDown = false;
    state_.attackLeft = false;
    state_.attackRight = false;
	state_.enter = false;

    mapping_.up = SDL_SCANCODE_W;
    mapping_.down = SDL_SCANCODE_S;
    mapping_.left = SDL_SCANCODE_A;
    mapping_.right = SDL_SCANCODE_D;
    mapping_.attack = SDL_SCANCODE_SPACE;
    mapping_.interact = SDL_SCANCODE_E;
    mapping_.menu = SDL_SCANCODE_ESCAPE;
    mapping_.attackUp = SDL_SCANCODE_UP;
    mapping_.attackDown = SDL_SCANCODE_DOWN;
    mapping_.attackLeft = SDL_SCANCODE_LEFT;
    mapping_.attackRight = SDL_SCANCODE_RIGHT;
	mapping_.enter = SDL_SCANCODE_RETURN;
}

void Input::keyDown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == mapping_.up) {
            state_.up = true;
		}
		if (event->keysym.scancode == mapping_.down) {
            state_.down = true;
		}
		if (event->keysym.scancode == mapping_.left) {
            state_.left = true;
		}
		if (event->keysym.scancode == mapping_.right) {
            state_.right = true;
		}
		if (event->keysym.scancode == mapping_.attack) {
            state_.attack = true;
		}
		if (event->keysym.scancode == mapping_.interact) {
            state_.interact = true;
		}
		if (event->keysym.scancode == mapping_.menu) {
            state_.menu = true;
		}
		if (event->keysym.scancode == mapping_.attackUp) {
            state_.attackUp = true;
		}
		if (event->keysym.scancode == mapping_.attackDown) {
            state_.attackDown = true;
		}
		if (event->keysym.scancode == mapping_.attackLeft) {
            state_.attackLeft = true;
		}
		if (event->keysym.scancode == mapping_.attackRight) {
            state_.attackRight = true;
		}
		if (event->keysym.scancode == mapping_.enter) {
            state_.enter = true;
		}
	}
}

void Input::keyUp(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == mapping_.up) {
            state_.up = false;
		}
		if (event->keysym.scancode == mapping_.down) {
            state_.down = false;
		}
		if (event->keysym.scancode == mapping_.left) {
            state_.left = false;
		}
		if (event->keysym.scancode == mapping_.right) {
            state_.right = false;
		}
		if (event->keysym.scancode == mapping_.attack) {
            state_.attack = false;
		}
		if (event->keysym.scancode == mapping_.interact) {
            state_.interact = false;
		}
		if (event->keysym.scancode == mapping_.menu) {
            state_.menu = false;
		}
		if (event->keysym.scancode == mapping_.attackUp) {
            state_.attackUp = false;
		}
		if (event->keysym.scancode == mapping_.attackDown) {
            state_.attackDown = false;
		}
		if (event->keysym.scancode == mapping_.attackLeft) {
            state_.attackLeft = false;
		}
		if (event->keysym.scancode == mapping_.attackRight) {
            state_.attackRight = false;
		}
		if (event->keysym.scancode == mapping_.enter) {
            state_.enter = false;
		}
	}
}

int Input::scan() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return 1;

            case SDL_KEYDOWN:
				keyDown(&event.key);
				break;

			case SDL_KEYUP:
				keyUp(&event.key);
				break;

       //TODO     case SDL_MOUSEBUTTONDOWN:
       //TODO     case SDL_MOUSEBUTTONUP:
       //TODO     case SDL_MOUSEMOTION:

			default:
				break;
		}
	}
    return 0;
}

InputState Input::getState() {
    return state_;
}

void Input::resetInteract() {
    state_.interact = false;
}

void Input::resetInput() {
	state_.attack = false;
	state_.down = false;
	state_.up = false;
	state_.right = false;
	state_.left = false;
	state_.interact = false;
	state_.menu = false;
	state_.attackDown = false;
	state_.attackLeft = false;
	state_.attackRight = false;
	state_.attackUp = false;
	state_.enter = false;
}

