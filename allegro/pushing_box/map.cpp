#include "map.h"

#include "box.h"
#include "character.h"
#include "entity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>
#include <string>
#include <vector>

extern int stage;

static const int max_width = 10;
static const int max_height = 10;
static const int unit_size = 48;
std::vector<std::vector<Terrain>> map(max_height, std::vector<Terrain>(max_width));
std::vector<std::vector<EntityType>> entity_map(max_height, std::vector<EntityType>(max_width));
std::vector<std::vector<void*>> entity_ptr(max_height, std::vector<void*>(max_width));

ALLEGRO_BITMAP *terr_img[4] = { nullptr };

void mapInit() {
	mapLoad(0);
	mapConnect();
}

void mapReset(int stage) {
	mapLoad(stage);
	mapConnect();
}

void mapLoad(int stage) {
	std::string path = "./map/stage";
	path += std::to_string(stage);

	FILE *fp;
	fopen_s(&fp, path.c_str(), "rb");
	if (fp == nullptr) {
		std::cout << "Open file fail: " << path << std::endl;
		return;
	}
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			int temp;
			fread(&temp, sizeof(int), 1, fp);
			map[i][j] = (Terrain)temp;
			std::cout << i << " " << j << " " << map[i][j] << std::endl;
		}
	}
	fclose(fp);
	printTerrainMap();
}

void mapConnect() {
	terr_img[1] = al_load_bitmap("./img/wall.png");
	terr_img[2] = al_load_bitmap("./img/road.png");
	terr_img[3] = al_load_bitmap("./img/target.png");
}

void mapShow() {
	for (int i = 0; i < max_width; ++i)
		for (int j = 0; j < max_height; ++j)
			if (map[i][j] != _none_terrain)
				al_draw_bitmap(terr_img[map[i][j]], j*unit_size, i*unit_size, 0);
}

void entityShow() {
	for (int i = 0; i < max_width; ++i) {
		for (int j = 0; j < max_height; ++j) {
			if (entity_map[i][j] == _none_entity) {
				continue;
			}
			else if (entity_map[i][j] == _character) {
				al_draw_bitmap(getBitmap(*(character*)(entity_ptr[i][j])), j*unit_size, i*unit_size, 0);
				// al_draw_bitmap(getBitmap(hero), i*unit_size, j*unit_size, 0);
			}
			else if (entity_map[i][j] == _box) {
				al_draw_bitmap(getBitmap(*(box*)(entity_ptr[i][j])), j*unit_size, i*unit_size, 0);
			}
			else {

			}
		}
	}
}

void printTerrainMap() {
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j)
			std::cout << map[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void printEntityMap() {
	for (int i = 0; i < entity_map.size(); ++i) {
		for (int j = 0; j < entity_map[0].size(); ++j)
			std::cout << entity_map[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void printEntityPtr() {
	for (int i = 0; i < entity_ptr.size(); ++i) {
		for (int j = 0; j < entity_ptr[0].size(); ++j)
			std::cout << entity_ptr[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void entityReset() {
	for (int i = 0; i < entity_ptr.size(); ++i) {
		for (int j = 0; j < entity_ptr[0].size(); ++j) {
			entity_map[i][j] = _none_entity;
			entity_ptr[i][j] = nullptr;
		}
	}
}

void textShow(ALLEGRO_FONT *text) {
	std::string level = "level ";
	level += std::to_string(stage);
	std::string step_str = "step  ";
	step_str += std::to_string(hero.step);
	al_draw_text(text, al_map_rgb(255, 255, 255), 500, 50, 0, level.data());
	al_draw_text(text, al_map_rgb(255, 255, 255), 500, 100, 0, step_str.data());
}