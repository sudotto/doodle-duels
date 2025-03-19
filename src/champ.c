#include <string.h>
#include <math.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "ui.h"

#include "champ.h"

Champ new_champ(SDL_Renderer* rend, char* name){
	Champ champ;
	champ.x = 10;
	champ.y = 10;
	champ.x_vel = 0;
	champ.y_vel = 0;
	champ.max_spd = 1;
	champ.accel = 1;
	champ.idle[LEFT] = new_cropped_img(rend, "assets/frank/idle.png", 0, 0, 32 * 10, 32 * 10);
	champ.idle[RIGHT] = new_cropped_img(rend, "assets/frank/idle.png", 0, 32 * 10, 32 * 10, 32 * 10);
	champ.facing = RIGHT;
	return champ;
}

void control_champ(Champ* champ, const bool* keystates){
	if(keystates[SDL_SCANCODE_W]){
	} else if(keystates[SDL_SCANCODE_A]){
		if(champ->x_vel != champ->max_spd){
			champ->x_vel -= champ->accel;
		}
		champ->facing = LEFT;
	} else if(keystates[SDL_SCANCODE_S]){
	} else if(keystates[SDL_SCANCODE_D]){
		if(champ->x_vel != champ->max_spd){
			champ->x_vel += champ->accel; 
		}
		champ->facing = RIGHT;
	}
}

void move_champ(Champ* champ){
	int friction = 1;
	champ->x += champ->x_vel;
	champ->y += champ->y_vel;
	if(champ->x_vel > friction){
		champ->x_vel += friction;
	} else if(champ->x_vel < -friction){
		champ->x_vel -= friction;
	} else {
		champ->x_vel = 0;
	}
	if(champ->y_vel != 0){
		champ->y_vel -= 1;
	}
}

void render_champ(SDL_Renderer* rend, Champ* champ){
	render_img(rend, &champ->idle[champ->facing], champ->x, champ->y, 64, 64);
}
