#include "character.h"

#include "box.h"
#include "entity.h"
#include "map.h"

#include <iostream>
#include <string>

extern bool passed;

character hero("hero");

void characterInit() {
    characterLoad(hero);
    updateEntityMapElement(hero, 0);
}

void characterReset(int stage) {
    // characterLoad(hero);
    updateEntityMapElement(hero, stage);
}

void characterLoad(character& ch) {
    std::string path = "./character/";
    std::string path_img = "./img/";
    path += ch.name;
    ch.img[_up] = al_load_bitmap((path_img + "up_" + ch.name + ".png").c_str());
    ch.img[_down] = al_load_bitmap((path_img + "down_" + ch.name + ".png").c_str());
    ch.img[_left] = al_load_bitmap((path_img + "left_" + ch.name + ".png").c_str());
    ch.img[_right] = al_load_bitmap((path_img + "right_" + ch.name + ".png").c_str());

    FILE *fp;
    fopen_s(&fp, path.c_str(), "rb");
    for (int i = 0; i < sav_pos; ++i)
        fread(&ch.position[i], sizeof(coord), 1, fp);
    fclose(fp);
}

void updateEntityMapElement(character& ch, int stage) {
    ch.cur_position = ch.position[stage];
    entity_map[ch.cur_position.x][ch.cur_position.y] = ch.et;
    entity_ptr[ch.cur_position.x][ch.cur_position.y] = &ch;
}

ALLEGRO_BITMAP* getBitmap(character& ch) {
    return ch.img[ch.dir];
}

void move_left(character& ch, bool flag) {

	ch.dir = _left;
    if (map[ch.cur_position.x][ch.cur_position.y - 1] == _wall)
        return;
    else if (entity_map[ch.cur_position.x][ch.cur_position.y - 1] == _box) {
        if (entity_map[ch.cur_position.x][ch.cur_position.y - 2] == _box ||
            map[ch.cur_position.x][ch.cur_position.y - 2] == _wall)
            return;
        else {
            entity_map[ch.cur_position.x][ch.cur_position.y - 2] = _box;
            entity_ptr[ch.cur_position.x][ch.cur_position.y - 2] = entity_ptr[ch.cur_position.x][ch.cur_position.y - 1];
			boxUpdatePosition((box*)entity_ptr[ch.cur_position.x][ch.cur_position.y - 2], coord(ch.cur_position.x, ch.cur_position.y - 2));
            entity_map[ch.cur_position.x][ch.cur_position.y - 1] = _character;
            entity_ptr[ch.cur_position.x][ch.cur_position.y - 1] = &ch;
			entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
			--ch.cur_position.y;
			(flag) ? ++ch.step : --ch.step;
        }
    }
    else {
        entity_map[ch.cur_position.x][ch.cur_position.y - 1] = _character;
        entity_ptr[ch.cur_position.x][ch.cur_position.y - 1] = &ch;
		entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
		entity_ptr[ch.cur_position.x][ch.cur_position.y] = nullptr;
		--ch.cur_position.y;
		(flag) ? ++ch.step : --ch.step;
    }
	updateBoxInst();
}

void move_right(character& ch, bool flag) {

	ch.dir = _right;
	if (map[ch.cur_position.x][ch.cur_position.y + 1] == _wall)
		return;
	else if (entity_map[ch.cur_position.x][ch.cur_position.y + 1] == _box) {
		if (entity_map[ch.cur_position.x][ch.cur_position.y + 2] == _box ||
			map[ch.cur_position.x][ch.cur_position.y + 2] == _wall)
			return;
		else {
			entity_map[ch.cur_position.x][ch.cur_position.y + 2] = _box;
			entity_ptr[ch.cur_position.x][ch.cur_position.y + 2] = entity_ptr[ch.cur_position.x][ch.cur_position.y + 1];
			boxUpdatePosition((box*)entity_ptr[ch.cur_position.x][ch.cur_position.y + 2], coord(ch.cur_position.x, ch.cur_position.y + 2));
			entity_map[ch.cur_position.x][ch.cur_position.y + 1] = _character;
			entity_ptr[ch.cur_position.x][ch.cur_position.y + 1] = &ch;
			entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
			++ch.cur_position.y;
			(flag) ? ++ch.step : --ch.step;
		}
	}
	else {
		entity_map[ch.cur_position.x][ch.cur_position.y + 1] = _character;
		entity_ptr[ch.cur_position.x][ch.cur_position.y + 1] = &ch;
		entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
		entity_ptr[ch.cur_position.x][ch.cur_position.y] = nullptr;
		++ch.cur_position.y;
		(flag) ? ++ch.step : --ch.step;
	}
	updateBoxInst();
}

void move_up(character& ch, bool flag) {
	ch.dir = _up;
	if (map[ch.cur_position.x - 1][ch.cur_position.y] == _wall)
		return;
	else if (entity_map[ch.cur_position.x - 1][ch.cur_position.y] == _box) {
		if (entity_map[ch.cur_position.x - 2][ch.cur_position.y] == _box ||
			map[ch.cur_position.x - 2][ch.cur_position.y] == _wall)
			return;
		else {
			entity_map[ch.cur_position.x - 2][ch.cur_position.y] = _box;
			entity_ptr[ch.cur_position.x - 2][ch.cur_position.y] = entity_ptr[ch.cur_position.x - 1][ch.cur_position.y];
			boxUpdatePosition((box*)entity_ptr[ch.cur_position.x - 2][ch.cur_position.y], coord(ch.cur_position.x - 2, ch.cur_position.y));
			entity_map[ch.cur_position.x - 1][ch.cur_position.y] = _character;
			entity_ptr[ch.cur_position.x - 1][ch.cur_position.y] = &ch;
			entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
			--ch.cur_position.x;
			(flag) ? ++ch.step : --ch.step;
		}
	}
	else {
		entity_map[ch.cur_position.x - 1][ch.cur_position.y] = _character;
		entity_ptr[ch.cur_position.x - 1][ch.cur_position.y] = &ch;
		entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
		entity_ptr[ch.cur_position.x][ch.cur_position.y] = nullptr;
		--ch.cur_position.x;
		(flag) ? ++ch.step : --ch.step;
	}
	updateBoxInst();
}

void move_down(character& ch, bool flag) {
	ch.dir = _down;
	if (map[ch.cur_position.x + 1][ch.cur_position.y] == _wall)
		return;
	else if (entity_map[ch.cur_position.x + 1][ch.cur_position.y] == _box) {
		if (entity_map[ch.cur_position.x + 2][ch.cur_position.y] == _box ||
			map[ch.cur_position.x + 2][ch.cur_position.y] == _wall)
			return;
		else {
			entity_map[ch.cur_position.x + 2][ch.cur_position.y] = _box;
			entity_ptr[ch.cur_position.x + 2][ch.cur_position.y] = entity_ptr[ch.cur_position.x + 1][ch.cur_position.y];
			boxUpdatePosition((box*)entity_ptr[ch.cur_position.x + 2][ch.cur_position.y], coord(ch.cur_position.x + 2, ch.cur_position.y));
			entity_map[ch.cur_position.x + 1][ch.cur_position.y] = _character;
			entity_ptr[ch.cur_position.x + 1][ch.cur_position.y] = &ch;
			entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
			++ch.cur_position.x;
			(flag) ? ++ch.step : --ch.step;
		}
	}
	else {
		entity_map[ch.cur_position.x + 1][ch.cur_position.y] = _character;
		entity_ptr[ch.cur_position.x + 1][ch.cur_position.y] = &ch;
		entity_map[ch.cur_position.x][ch.cur_position.y] = _none_entity;
		entity_ptr[ch.cur_position.x][ch.cur_position.y] = nullptr;
		++ch.cur_position.x;
		(flag) ? ++ch.step : --ch.step;
	}
	updateBoxInst();
}

void updateBoxInst() {
	passed = true;
	for (auto &box : box_inst) {
		box.isValid = (map[box.position.x][box.position.y] == _target);
		if (!box.isValid)
			passed = false;
	}
}