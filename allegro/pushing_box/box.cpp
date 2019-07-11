#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "map.h"

#define TURN_UP     (0)
#define TURN_DOWN   (1)
#define TURN_LEFT   (2)
#define TURN_RIGHT  (3)
#define REFRESH     (4)
#define EXIT        (-1)

#define MAN_UP              (0)
#define MAN_DOWN            (1)
#define MAN_LEFT            (2)
#define MAN_RIGHT           (3)
#define BOX                 (4)
#define MAN_UP_TARGET       (5)
#define MAN_DOWN_TARGET     (6)
#define MAN_LEFT_TARGET     (7)
#define MAN_RIGHT_TARGET    (8)
#define BOX_TARGET          (9)
#define WALL                (10)
#define TARGET              (11)
#define ROAD                (12)
#define TARGET2BASE         (-5)
#define BASE2TARGET         (+5)
#define IS_TARGET(x)        (x >= 5 && x <= 9)

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *wall = NULL;
ALLEGRO_BITMAP *target = NULL;
ALLEGRO_BITMAP *road = NULL;
ALLEGRO_BITMAP *man[4] = { NULL };
ALLEGRO_BITMAP *box[2] = { NULL };
ALLEGRO_EVENT *event = new ALLEGRO_EVENT;
ALLEGRO_EVENT_QUEUE *queue = NULL;

int game_init();
int game_destroy();
int game_show();
int game_run();
int game_msg();
int init_map(int i);
int update_map(int move);
int draw_map();

int map[10][10];
int move_x[4] = { -1, 1, 0, 0 };
int move_y[4] = { 0, 0, -1, 1 };
int x;
int y;

int main()
{
	game_init();
	game_run();
	game_destroy();
}

int game_init()
{
	al_init();
	al_install_keyboard();
	al_init_image_addon();

	display = al_create_display(480, 480);
	al_set_window_title(display, "Pushing Box");

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	wall = al_load_bitmap("wall.png");
	target = al_load_bitmap("target.png");
	road = al_load_bitmap("road.png");
	box[0] = al_load_bitmap("box0.png");
	box[1] = al_load_bitmap("box1.png");
	man[0] = al_load_bitmap("up.png");
	man[1] = al_load_bitmap("down.png");
	man[2] = al_load_bitmap("left.png");
	man[3] = al_load_bitmap("right.png");
	init_map(0);

	return 0;
}

int game_destroy()
{
	al_uninstall_keyboard();
	al_destroy_bitmap(wall);
	al_destroy_bitmap(target);
	al_destroy_bitmap(road);
	for (int i = 0; i < 4; ++i)
		al_destroy_bitmap(man[i]);
	for (int i = 0; i < 2; ++i)
		al_destroy_bitmap(box[i]);

	return 0;
}

int game_show()
{
	// al_clear_to_color(al_map_rgb(0, 0, 0));
	draw_map();
	al_flip_display();
	return 0;
}

int game_run()
{
	bool running = true;
	while (running)
	{
		game_show();
		if (!al_event_queue_is_empty(queue))
		{
			int res = game_msg();
			if (res == EXIT)
				running = false;
			else
				update_map(res);
		}

	}
	return 0;
}

int game_msg()
{
	al_wait_for_event(queue, event);
	if (event->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		return EXIT;
	if (event->type == ALLEGRO_EVENT_KEY_CHAR)
	{
		if (event->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			return EXIT;
		else if (event->keyboard.keycode == ALLEGRO_KEY_UP)
			return TURN_UP;
		else if (event->keyboard.keycode == ALLEGRO_KEY_DOWN)
			return TURN_DOWN;
		else if (event->keyboard.keycode == ALLEGRO_KEY_LEFT)
			return TURN_LEFT;
		else if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT)
			return TURN_RIGHT;
		else if (event->keyboard.keycode == ALLEGRO_KEY_F5)
			return REFRESH;
	}
	return 66;
}

int init_map(int i)
{
	x = 7;
	y = 5;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			map[i][j] = map_stage_0[i][j];

	return 0;
}

int update_map(int move)
{
	if (move == TURN_UP)
		goto UP;
	if (move == TURN_DOWN)
		goto DOWN;
	if (move == TURN_LEFT)
		goto LEFT;
	if (move == TURN_RIGHT)
		goto RIGHT;
	if (move == REFRESH)
		goto F5;
	return 0;

UP:
	if (map[x - 1][y] == WALL)
		;
	else if (map[x - 1][y] == TARGET)
	{
		map[x - 1][y] = MAN_UP_TARGET;
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		--x;
	}
	else if (map[x - 1][y] == ROAD)
	{
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		map[x - 1][y] = MAN_UP;
		--x;
	}
	else if (map[x - 1][y] == BOX)
	{
		if (map[x - 2][y] == ROAD)
		{
			map[x - 2][y] = BOX;
			map[x - 1][y] = MAN_UP;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--x;
		}
		else if (map[x - 2][y] == TARGET)
		{
			map[x - 2][y] = BOX_TARGET;
			map[x - 1][y] = MAN_UP;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--x;
		}
	}
	else if (map[x - 1][y] == BOX_TARGET)
	{
		if (map[x - 2][y] == ROAD)
		{
			map[x - 2][y] = BOX;
			map[x - 1][y] = MAN_UP_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--x;
		}
		else if (map[x - 2][y] == TARGET)
		{
			map[x - 2][y] = BOX_TARGET;
			map[x - 1][y] = MAN_UP_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--x;
		}
	}
	return 0;
DOWN:
	if (map[x + 1][y] == WALL)
		;
	else if (map[x + 1][y] == TARGET)
	{
		map[x + 1][y] = MAN_DOWN_TARGET;
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		++x;
	}
	else if (map[x + 1][y] == ROAD)
	{
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		map[x + 1][y] = MAN_DOWN;
		++x;
	}
	else if (map[x + 1][y] == BOX)
	{
		if (map[x + 2][y] == ROAD)
		{
			map[x + 2][y] = BOX;
			map[x + 1][y] = MAN_DOWN;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++x;
		}
		else if (map[x + 2][y] == TARGET)
		{
			map[x + 2][y] = BOX_TARGET;
			map[x + 1][y] = MAN_DOWN;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++x;
		}
	}
	else if (map[x + 1][y] == BOX_TARGET)
	{
		if (map[x + 2][y] == ROAD)
		{
			map[x + 2][y] = BOX;
			map[x + 1][y] = MAN_DOWN_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++x;
		}
		else if (map[x + 2][y] == TARGET)
		{
			map[x + 2][y] = BOX_TARGET;
			map[x + 1][y] = MAN_DOWN_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++x;
		}
	}
	return 0;
LEFT:
	if (map[x][y - 1] == WALL)
		;
	else if (map[x][y - 1] == TARGET)
	{
		map[x][y - 1] = MAN_LEFT_TARGET;
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		--y;
	}
	else if (map[x][y - 1] == ROAD)
	{
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		map[x][y - 1] = MAN_LEFT;
		--y;
	}
	else if (map[x][y - 1] == BOX)
	{
		if (map[x][y - 2] == ROAD)
		{
			map[x][y - 2] = BOX;
			map[x][y - 1] = MAN_LEFT;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--y;
		}
		else if (map[x][y - 2] == TARGET)
		{
			map[x][y - 2] = BOX_TARGET;
			map[x][y - 1] = MAN_LEFT;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--y;
		}
	}
	else if (map[x][y - 1] == BOX_TARGET)
	{
		if (map[x][y - 2] == ROAD)
		{
			map[x][y - 2] = BOX;
			map[x][y - 1] = MAN_LEFT_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--y;
		}
		else if (map[x][y - 2] == TARGET)
		{
			map[x][y - 2] = BOX_TARGET;
			map[x][y - 1] = MAN_LEFT_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			--y;
		}
	}
	return 0;
RIGHT:
	if (map[x][y + 1] == WALL)
		;
	else if (map[x][y + 1] == TARGET)
	{
		map[x][y + 1] = MAN_RIGHT_TARGET;
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		++y;
	}
	else if (map[x][y + 1] == ROAD)
	{
		map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
		map[x][y + 1] = MAN_RIGHT;
		++y;
	}
	else if (map[x][y + 1] == BOX)
	{
		if (map[x][y + 2] == ROAD)
		{
			map[x][y + 2] = BOX;
			map[x][y + 1] = MAN_RIGHT;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++y;
		}
		else if (map[x][y + 2] == TARGET)
		{
			map[x][y + 2] = BOX_TARGET;
			map[x][y + 1] = MAN_RIGHT;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++y;
		}
	}
	else if (map[x][y + 1] == BOX_TARGET)
	{
		if (map[x][y + 2] == ROAD)
		{
			map[x][y + 2] = BOX;
			map[x][y + 1] = MAN_RIGHT_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++y;
		}
		else if (map[x][y + 2] == TARGET)
		{
			map[x][y + 2] = BOX_TARGET;
			map[x][y + 1] = MAN_RIGHT_TARGET;
			map[x][y] = (map[x][y] > 4) ? TARGET : ROAD;
			++y;
		}
	}
	return 0;
F5:
	init_map(0);
	return 0;

}

int draw_map()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (map[i][j] == WALL)
				al_draw_bitmap(wall, 48 * j, 48 * i, 0);
			else if (map[i][j] == TARGET)
				al_draw_bitmap(target, 48 * j, 48 * i, 0);
			else if (map[i][j] == MAN_UP || map[i][j] == MAN_UP_TARGET)
				al_draw_bitmap(man[0], 48 * j, 48 * i, 0);
			else if (map[i][j] == MAN_DOWN || map[i][j] == MAN_DOWN_TARGET)
				al_draw_bitmap(man[1], 48 * j, 48 * i, 0);
			else if (map[i][j] == MAN_LEFT || map[i][j] == MAN_LEFT_TARGET)
				al_draw_bitmap(man[2], 48 * j, 48 * i, 0);
			else if (map[i][j] == MAN_RIGHT || map[i][j] == MAN_RIGHT_TARGET)
				al_draw_bitmap(man[3], 48 * j, 48 * i, 0);
			else if (map[i][j] == BOX)
				al_draw_bitmap(box[0], 48 * j, 48 * i, 0);
			else if (map[i][j] == BOX_TARGET)
				al_draw_bitmap(box[1], 48 * j, 48 * i, 0);
			else if (map[i][j] == ROAD)
				al_draw_bitmap(road, 48 * j, 48 * i, 0);
		}
	}

	return 0;
}