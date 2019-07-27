#include "game.h"

#include "display.h"
#include "eventhandler.h"

#include "map.h"

#include "character.h"
#include "item.h"
#include "box.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>

int stage = 0;
const int total_stage = 10;
bool passed = false;

static void allegroInit() {
	al_init();
	al_init_image_addon();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
}

void game() {
	gameInit();
	gameRun();
	gameDestroy();
}

void gameInit() {
	allegroInit();
	displayInit(640, 480);
	eventHandlerInit(display);
	mapInit();
	characterInit();
	boxInit();
}

void gameRun() {
	bool running = true;
	while (running) {
		mapShow();
		entityShow();
		displayShow();
		running = eventHandler(getEvent());
	}
}

void gameDestroy() {
	al_uninstall_keyboard();
}