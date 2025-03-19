#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

#include "ui.h"

typedef enum {
	LEFT,
	RIGHT
} Facing;

typedef struct {
	char* name;
	Img idle[2];
	Facing facing;
	int x;
	int y;
	float x_vel;
	float y_vel;
	float max_spd;
	float accel;
} Champ;

Champ new_champ(SDL_Renderer* rend, char* name);
void control_champ(Champ* champ, const bool* keystates);
void move_champ(Champ* champ);
void render_champ(SDL_Renderer* rend, Champ* champ);

#endif
