#include "eventhandler.h"

#include "box.h"
#include "character.h"
#include "map.h"

#include <allegro5/allegro.h>

#include <iostream>
#include <stack>
#include <windows.h>

extern int stage;
extern bool passed;

ALLEGRO_EVENT *event = new ALLEGRO_EVENT;
ALLEGRO_EVENT_QUEUE *queue = NULL;
std::stack<Direction> path;

void eventHandlerInit(ALLEGRO_DISPLAY *display) {
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
}

EventType getEvent() {
	if (!al_event_queue_is_empty(queue)) {
		al_wait_for_event(queue, event);
		if (event->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			return EventType::_end;
		if (event->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (event->keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				return EventType::_end;
			else if (event->keyboard.keycode == ALLEGRO_KEY_UP)
				return EventType::_turn_up;
			else if (event->keyboard.keycode == ALLEGRO_KEY_DOWN)
				return EventType::_turn_down;
			else if (event->keyboard.keycode == ALLEGRO_KEY_LEFT)
				return EventType::_turn_left;
			else if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT)
				return EventType::_turn_right;
			else if (event->keyboard.keycode == ALLEGRO_KEY_F5)
				return EventType::_refresh;
			else if (event->keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
				return EventType::_back;
		}
	}
	return EventType::_normal;
}

bool eventHandler(EventType event) {

	if (event == _end)
		return false;
	else if (event == _refresh) {
		stageReset(stage);
		while (!path.empty())
			path.pop();
	}
	else if (event == _turn_up) {
		move_up(hero, true);
		path.push(_up);
		isNextStage();
	}
	else if (event == _turn_down) {
		move_down(hero, true);
		path.push(_down);
		isNextStage();
	}
	else if (event == _turn_left) {
		move_left(hero, true);
		path.push(_left);
		isNextStage();
	}
	else if (event == _turn_right) {
		move_right(hero, true);
		path.push(_right);
		isNextStage();
	}
	else if (event == _back) {
		if (path.empty())
			return true;
		if (path.top() == _up)
			move_down(hero, false);
		else if (path.top() == _down)
			move_up(hero, false);
		else if (path.top() == _left)
			move_right(hero, false);
		else if (path.top() == _right)
			move_left(hero, false);
		path.pop();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	
	return true;
}

void stageReset(int stage) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	entityReset();
	mapReset(stage);
	characterReset(stage);
	boxReset(stage);
}

void isNextStage() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	if (passed) {
		passed = false;
		if (++stage == 10) {
			return;
		}
		stageReset(stage);
	}
}