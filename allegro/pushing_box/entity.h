#ifndef ENTITY__
#define ENTITY__

#include <iostream>

enum EntityType { _none_entity, _character, _box, _item };
enum Direction { _up, _down, _right, _left };

typedef struct Coord {
	int x;
	int y;

	Coord() {};
	Coord(int _x, int _y) : x(_x), y(_y) {};
	bool operator==(const Coord &c) const {
		return (this->x == c.x && this->y == c.y);
	}
	bool operator!=(const Coord &c) const {
		return !(*this == c);
	}
	void print() {
		std::cout << x << ' ' << y << std::endl;
	}
} coord;

#endif // !ENTITY__
