#ifndef MAP__
#define MAP__

#include "entity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <vector>

enum Terrain { _none_terrain, _wall, _road, _target };

void mapInit();
void mapReset(int stage);
void mapLoad(int stage);
void mapConnect();
void mapShow();
void entityShow();
void printTerrainMap();
void printEntityMap();
void printEntityPtr();
void entityReset();
void textShow(ALLEGRO_FONT *text);

extern std::vector<std::vector<Terrain>> map;
extern std::vector<std::vector<EntityType>> entity_map;
extern std::vector<std::vector<void*>> entity_ptr;

#endif // !MAP__

