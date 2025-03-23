#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "ui.h"

#include "champ.h"

Champ new_champ(SDL_Renderer* rend, char* name, float walk_spd, float accel){
	Champ champ;
	champ.x = 10;
	champ.y = 10;
	champ.w = 64;
	champ.h = 64;
	champ.x_vel = 0;
	champ.y_vel = 0;
	champ.walk_spd = 10;
	champ.air_spd = 15;
	champ.jump_spd = 15;
	champ.in_air = false;

	champ.facing = RIGHT;
	champ.anim_frame = 0;

	char* dirname = malloc(sizeof(char) * 20);
	// If in the future you are searching through the files wondering why a new character's sprites won't load this malloc might be why
	strcpy(dirname, "assets/");
	strcat(dirname, name);

	char* filepath = malloc(sizeof(char) * 20);
	strcpy(filepath, dirname);
	strcat(filepath, "/punch.png");

	for(int y = 0; y < 2; y++){
		champ.idle[y] = new_anim(rend, filepath, 4, y, 32 * 10, 32 * 10);
	}

	free(dirname);
	free(filepath);

	//champ.anim = &champ.idle;

	return champ;
}

void control_champ(Champ* champ, const bool* keystates){
	if(keystates[SDL_SCANCODE_W]){
		if(!champ->in_air){
			champ->y_vel = -champ->jump_spd;
		}
	}
	if(keystates[SDL_SCANCODE_A]){
		if(champ->in_air){
			champ->x_vel = -champ->air_spd;
		} else {
			champ->x_vel = -champ->walk_spd;
		}
		champ->facing = LEFT;
	}
	if(keystates[SDL_SCANCODE_S]){
	}
	if(keystates[SDL_SCANCODE_D]){
		if(champ->in_air){
			champ->x_vel = champ->air_spd;
		} else {
			champ->x_vel = champ->walk_spd;
		}
		champ->x_vel = champ->walk_spd; 
		champ->facing = RIGHT;
	}
}

void move_champ(Champ* champ){
	int floor = 300;
	float gravity = 1;
	int friction = 1;

	champ->y += champ->y_vel;
	champ->y_vel += gravity;
	if(champ->y + champ->h > floor){
		champ->y = floor - champ->h;
		champ->y_vel = 0;
		champ->in_air = false;
	} else {
		champ->in_air = true;
	}

	printf("%f\n", champ->x_vel);
	champ->x += champ->x_vel;
	if(champ->x_vel < 0){
		champ->x_vel += 1;
	} else if(champ->x_vel > 0){
		champ->x_vel -= 1;
	} else {
		champ->x_vel = 0;
	}
}

void render_champ(SDL_Renderer* rend, Champ* champ){
	render_anim(rend, &champ->idle[champ->facing], champ->x, champ->y, champ->w, champ->h, 0.1);
}
