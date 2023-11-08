#include <SDL2/SDL_events.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include "entity.hpp"
#include "game.hpp"
#include "renderer.hpp"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720


Game game;
// Initialize window and renderer
void initSDL(Game* game) {
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

    SDL_Window* w;
	w = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    /*
	if (w) {
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
    }
    */
	
    game->window = w;

	if (!game->window) {
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	game->renderer = SDL_CreateRenderer(game->window, -1, rendererFlags);

	if (!game->renderer) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			game.up = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			game.down = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			game.left = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			game.right = 1;
		}
	}
}

void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			game.up = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			game.down = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			game.left = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			game.right = 0;
		}
	}
}
// Input event
int doInput(void) {

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



void prepareScene(Game* game) {
	SDL_SetRenderDrawColor(game->renderer, 96, 128, 255, 255);
	SDL_RenderClear(game->renderer);
}


void presentScene(Game* game) {
	SDL_RenderPresent(game->renderer);
}


SDL_Texture* loadTexture(Game* game, const char* filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(game->renderer, filename);
	return texture;
}


void drawTexture(Game* game, SDL_Texture* texture, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(game->renderer, texture, NULL, &dest);
}


void exit_game(Game* game) {
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}



void sdltest() {
    Entity player;


    memset(&game, 0, sizeof(Game));
    memset(&player, 0, sizeof(Entity));

    initSDL(&game);

    player.x = 100;
    player.y = 100;

    player.texture = loadTexture(&game, "./assets/dude.png");

    int quit = 0;

    while (!quit) {

        prepareScene(&game);

        quit = doInput();
		
		if (game.up)
		{
			player.y -= 1;
		}

		if (game.down)
		{
			player.y += 1;
		}

		if (game.left)
		{
			player.x -= 1;
		}

		if (game.right)
		{
			player.x += 1;
		}

        drawTexture(&game, player.texture, player.x, player.y);

        presentScene(&game);

        SDL_Delay(1);
    }


    exit_game(&game);

}

