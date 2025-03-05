#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "ui.h"

Img new_img(SDL_Renderer* rend, char* file){
	Img img;
	img.surf = IMG_Load(file);
	img.tex = SDL_CreateTextureFromSurface(rend, img.surf);
	return img;
}

Img crop_img(Img *img, int x, int y, int w, int h){
	SDL_FRect src;
	src.x = x;
	src.y = y;
	src.w = w;
	src.h = h;
	img->crop = src;
}

void render_img(SDL_Renderer* rend, Img *img, int x, int y, int w, int h){
	SDL_FRect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	SDL_RenderTexture(rend, img->tex, NULL, &dest);
}
