#ifndef BOX__
#define BOX__

#include "entity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <vector>

typedef struct __box {
	const EntityType et = _box;
	bool isValid = false;
	coord position;
} box;

extern std::vector<box> box_inst;

void boxInit();
void boxReset(int stage);
void boxLoad(int stage);
void boxConnect();
ALLEGRO_BITMAP* getBitmap(box& cur);
ALLEGRO_BITMAP* getBitmap(box *cur);
void boxUpdatePosition(box* cur, coord position);

#endif // !BOX__
