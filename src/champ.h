#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

#include "ui.h"

typedef enum {
	LEFT,
	RIGHT
} Facing;

typedef enum {
	IDLE,
	WALK,
	PUNCH,
	FALLING
} Curr_anim;

typedef struct {
	char* name;
	Anim anims[4][2];
	Curr_anim anim;
	Facing facing;
	float x;
	float y;
	int w;
	int h;
	float x_vel;
	float y_vel;
	int walk_spd;
	int air_spd;
	int jump_spd;
	float accel;
	bool grounded;
} Champ;

Champ new_champ(SDL_Renderer* rend, char* name, float walk_spd, float accel);
void control_champ(Champ* champ, const bool* keystates);
void move_champ(Champ* champ);
void render_champ(SDL_Renderer* rend, Champ* champ);

#endif
