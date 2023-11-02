#include <SDL2/SDL_events.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720



typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} Game;

typedef struct {
    // player here???
	int x;
	int y;
	SDL_Texture *texture;
} Entity;


// Initialize window and renderer
void initSDL(Game* game) {
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	game->window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

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


// Input event
int doInput(void) {

	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return 1;

            case SDL_KEYDOWN:
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


int main() {
    Game game;
    Entity player;

    memset(&game, 0, sizeof(Game));
    memset(&player, 0, sizeof(Entity));

    initSDL(&game);

    player.x = 100;
    player.y = 100;

    player.texture = loadTexture(&game, "./texture.png");

    int quit = 0;

    while (!quit) {

        prepareScene(&game);

        quit = doInput();

        drawTexture(&game, player.texture, player.x, player.y);

        presentScene(&game);

        SDL_Delay(1);
    }

    exit_game(&game);

}


