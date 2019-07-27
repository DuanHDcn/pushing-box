#include "display.h"

#include "map.h"

#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

ALLEGRO_DISPLAY *display = NULL;
static ALLEGRO_BITMAP *icon = NULL;
ALLEGRO_FONT *font = NULL;

void displayInit(int w, int h) {
	display = al_create_display(w, h);
	al_set_window_title(display, "Pushing Box");
	icon = al_load_bitmap("./img/icon48.png");
	al_set_display_icon(display, icon);

	font = al_load_ttf_font("consola.ttf", 24, 0);
	if (font == NULL)
		std::cout << "Font Error" << std::endl;
}

void displayShow() {
	textShow(font);
	al_flip_display();
}
