#ifndef CHARACTER__
#define CHARACTER__

#include "entity.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include <string>

const int sav_pos = 20;

typedef struct __character {
	const EntityType et = _character;
	int step = 0;
	Direction dir = _up;
	coord cur_position;
	coord position[sav_pos];
	std::string name;
	ALLEGRO_BITMAP *img[4];

	__character(std::string name) { this->name = name; }
} character;

extern character hero;

void characterInit();
void characterReset(int stage);
void characterLoad(character& ch);
void updateEntityMapElement(character& ch, int stage);
ALLEGRO_BITMAP* getBitmap(character& ch);
void move_up(character& ch, bool flag);
void move_down(character& ch, bool flag);
void move_left(character& ch, bool flag);
void move_right(character& ch, bool flag);
void updateBoxInst();

#endif
