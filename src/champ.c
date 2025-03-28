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
	champ.walk_spd = 0;
	champ.air_spd = 10;
	champ.jump_spd = 15;
	champ.grounded = false;

	champ.facing = RIGHT;

	char* dirname = malloc(sizeof(char) * 20);
	// If in the future you are searching through the files wondering why a new character's sprites won't load this malloc might be why
	strcpy(dirname, "assets/");
	strcat(dirname, name);

	char* filepath = malloc(sizeof(char) * 30);

	char* filenames[4] = {
		"/idle.png",
		"/walk.png",
		"/punch.png",
		"/falling.png"
	};

	for(int anim = 0; anim < 4; anim++){
		for(int facing = 0; facing < 2; facing++){
			strcpy(filepath, dirname);
			strcat(filepath, filenames[anim]);
			champ.anims[anim][facing] = new_anim(rend, filepath, 4, facing, 32 * 10, 32 * 10);
		}
	}

	champ.anim = IDLE;

	free(dirname);
	free(filepath);
	return champ;
}

void control_champ(Champ* champ, const bool* keystates){
	champ->anim = IDLE;
	if(keystates[SDL_SCANCODE_W]){
		if(champ->grounded){
			champ->y_vel = -champ->jump_spd;
		}
	}
	if(keystates[SDL_SCANCODE_A]){
		champ->x_vel = -champ->walk_spd;
		if(!champ->grounded){
			champ->x_vel = -champ->air_spd;
		}
		champ->anim = WALK;
		champ->facing = LEFT;
	}
	if(keystates[SDL_SCANCODE_S]){
	}
	if(keystates[SDL_SCANCODE_D]){
		champ->x_vel = champ->walk_spd;
		if(!champ->grounded){
			champ->x_vel = champ->air_spd;
		}
		champ->anim = WALK;
		champ->facing = RIGHT;
	}
	if(!champ->grounded){
		champ->anim = FALLING;
	}
}

void move_champ(Champ* champ){
	int floor = 300;
	float gravity = 1;
	int friction = 1;

	champ->y += champ->y_vel;
	champ->y_vel += gravity;
	
	champ->grounded = false;
	if(champ->y + champ->h > floor){
		champ->y = floor - champ->h;
		champ->y_vel = 0;
		champ->grounded = true;
	}

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
	render_anim(rend, &champ->anims[champ->anim][champ->facing], champ->x, champ->y, champ->w, champ->h, 0.1);
}
