#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "ui.h"
#include "champ.h"

void framerate_cap(Uint8 fps, Uint32 frame_start){
	Uint32 frame_time = SDL_GetTicks() - frame_start;
	if(frame_time < 1/fps){
		SDL_Delay(1/fps - frame_time);
	}
}

void render_cursor(SDL_Renderer* rend, Img cursor, float mouse_x, float mouse_y, float old_mouse_x, float old_mouse_y){
	render_img(rend, &cursor, mouse_x, mouse_y, 32, 32);
}

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win = SDL_CreateWindow("Doodle Duels (by: sudotto)", 900, 600, 0);
	SDL_Renderer* rend = SDL_CreateRenderer(win, NULL);
	SDL_Event event;

	Img icon = new_img(rend, "assets/icon.png");
	Img logo = new_img(rend, "assets/logo.png");
	Img cursor = new_img(rend, "assets/cursor.png");
	SDL_SetWindowIcon(win, icon.surf);

	Champ champ = new_champ(rend, "frank", 100, 10);
	Champ champ_farnk = new_champ(rend, "frank", 100, 0);

	const bool* keystates = SDL_GetKeyboardState(NULL);
	float mouse_x;
	float mouse_y;
	float old_mouse_x;
	float old_mouse_y;
	SDL_HideCursor();
	Uint32 frame_start;
	bool running = true;

	while(running){
		frame_start = SDL_GetTicks();

		keystates = SDL_GetKeyboardState(NULL);
		old_mouse_x = mouse_x;
		old_mouse_y = mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_EVENT_QUIT:
					running = false;
					break;
			}
		}
		control_champ(&champ, keystates);
		control_champ(&champ_farnk, keystates);
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 1);
		SDL_RenderClear(rend);

		render_img(rend, &logo, 100, 100, 256, 32);
		
		move_champ(&champ_farnk);
		render_champ(rend, &champ_farnk);

		move_champ(&champ);
		render_champ(rend, &champ);

		render_cursor(rend, cursor, mouse_x, mouse_y, old_mouse_x, old_mouse_y);
		SDL_RenderPresent(rend);
		framerate_cap(60, frame_start);
	}
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
}
