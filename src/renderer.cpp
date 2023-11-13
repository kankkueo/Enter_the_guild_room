#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include "renderer.hpp"


Renderer::Renderer() {
	renderer_flags_ = SDL_RENDERER_ACCELERATED;
	window_flags_ = SDL_WINDOW_FULLSCREEN;
}

void Renderer::initSDL() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window_ = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags_);

	if (!window_) {
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer_ = SDL_CreateRenderer(window_, -1, renderer_flags_);

	if (!renderer_) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}

void Renderer::prepareScene() {
	SDL_SetRenderDrawColor(renderer_, 96, 128, 255, 255);
	SDL_RenderClear(renderer_);
}

void Renderer::presentScene() {
	SDL_RenderPresent(renderer_);
}

SDL_Texture* Renderer::loadTexture(const char* filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(renderer_, filename);
	return texture;
}

void Renderer::drawTexture(SDL_Texture* texture, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer_, texture, NULL, &dest);
}

void Renderer::destroy() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

