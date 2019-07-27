#include "box.h"

#include "entity.h"
#include "map.h"

#include <iostream>
#include <string>
#include <vector>

ALLEGRO_BITMAP *img[2];
std::vector<box> box_inst;

void boxInit() {
	boxLoad(0);
	boxConnect();
}

void boxReset(int stage) {
	box_inst.clear();
	boxLoad(stage);
	boxConnect();
}

void boxLoad(int stage) {
	std::string path = "./box/stage";
	path += std::to_string(stage);
	std::cout << path << std::endl;

	FILE *fp;
	fopen_s(&fp, path.c_str(), "rb");
	
	int size;
	fread(&size, sizeof(int), 1, fp);
	
	box box_temp;
	
	for (int i = 0; i < size; ++i) {
		fread(&box_temp.position, sizeof(coord), 1, fp);
		box_inst.push_back(box_temp);
	}

	for (auto &box : box_inst) {
		box.isValid = (map[box.position.x][box.position.y] == _target);
		entity_map[box.position.x][box.position.y] = _box;
		entity_ptr[box.position.x][box.position.y] = &box;
		std::cout << box.position.x << " " << box.position.y << std::endl;
	}
	
	fclose(fp);
}

void boxConnect() {
	img[0] = al_load_bitmap("./img/box_false.png");
	img[1] = al_load_bitmap("./img/box_true.png");
}

ALLEGRO_BITMAP* getBitmap(box& cur) {
	return cur.isValid ? img[1] : img[0];
}

ALLEGRO_BITMAP* getBitmap(box *cur) {
	return cur->isValid ? img[1] : img[0];
}

void boxUpdatePosition(box* cur, coord position) {
	cur->position = position;
}