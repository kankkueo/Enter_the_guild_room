#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include "renderer.hpp"



Renderer::Renderer(int width, int height, uint32_t r_flags, uint32_t w_flags) {

	width_ = width;
	height_ = height;
	renderer_flags_ = r_flags;
	window_flags_ = w_flags;
	font_ = TTF_OpenFont("./assets/fonts/Ubuntu-C.ttf", 24);
	//renderer_flags_ = SDL_RENDERER_ACCELERATED;
	//window_flags_ = SDL_WINDOW_FULLSCREEN;
	//window_flags_ = 0;


}

void Renderer::initSDL() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window_ = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, width_, height_, window_flags_);

	if (!window_) {
		printf("Failed to open %d x %d window: %s\n", width_, height_, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer_ = SDL_CreateRenderer(window_, -1, renderer_flags_);

	if (!renderer_) {
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	TTF_Init();
	TTF_Font *font = TTF_OpenFont("", 24);
}

void Renderer::prepareScene() {
	SDL_SetRenderDrawColor(renderer_, 40, 40, 40, 255);
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

int Renderer::getWinWidth() {
    return width_;
}

int Renderer::getWinHeight() {
    return height_;
}

void Renderer::draw_text(char* text, int x, int y){
	
}

