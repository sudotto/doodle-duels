#ifndef UI
#define UI

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef struct {
	SDL_Surface* surf;
	SDL_Texture* tex;
	SDL_FRect crop;
	bool cropped;
} Img;

Img new_img(SDL_Renderer* rend, char* filename);
Img new_cropped_img(SDL_Renderer* rend, char* file, int x, int y, int w, int h);
void render_img(SDL_Renderer* rend, Img* img, int x, int y, int w, int h);

#endif
