#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

void doKeyDown(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
		}
	}
}

void doKeyUp(SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
		}
	}
}


int doInput() {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return 1;

            case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

			default:
				break;
		}
	}
    return 0;
}


