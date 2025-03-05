#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "ui.h"

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win = SDL_CreateWindow("Skribble Skirmish", 900, 600, 0);
	SDL_Renderer* rend = SDL_CreateRenderer(win, NULL);
	SDL_Event event;

	Img icon = new_img(rend, "assets/logo.png");
	Img cursor = new_img(rend, "assets/cursor.png");
	SDL_SetWindowIcon(win, icon.surf);

	float mouse_x;
	float mouse_y;

	SDL_HideCursor();

	bool running = true;

	while(running){
		SDL_GetMouseState(&mouse_x, &mouse_y);
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_EVENT_QUIT:
					running = false;
					break;
			}
		}
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 1);
		SDL_RenderClear(rend);

		render_img(rend, &cursor, mouse_x, mouse_y, 30, 30);

		SDL_RenderPresent(rend);
	}
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
}
