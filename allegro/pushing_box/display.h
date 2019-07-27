#ifndef DISPLAY__
#define DISPLAY__

#include <allegro5/allegro.h>

extern ALLEGRO_DISPLAY *display;

void displayInit(int w, int h);
void displayShow();

#endif // !DISPLAY__
