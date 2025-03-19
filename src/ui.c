#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "ui.h"

Img new_img(SDL_Renderer* rend, char* file){
	Img img;
	img.surf = IMG_Load(file);
	img.tex = SDL_CreateTextureFromSurface(rend, img.surf);
	img.cropped = false;
	return img;
}

Img new_cropped_img(SDL_Renderer* rend, char* file, int x, int y, int w, int h){
	Img img;
	img.surf = IMG_Load(file);
	img.tex = SDL_CreateTextureFromSurface(rend, img.surf);
	img.crop.x = x;
	img.crop.y = y;
	img.crop.w = w;
	img.crop.h = h;
	img.cropped = true;
	return img;
}

void render_img(SDL_Renderer* rend, Img *img, int x, int y, int w, int h){
	SDL_FRect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	if(img->cropped){
		SDL_RenderTexture(rend, img->tex, &img->crop, &dest);
	} else {
		SDL_RenderTexture(rend, img->tex, NULL, &dest);
	}
}
