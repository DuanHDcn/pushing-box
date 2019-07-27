#ifndef EVENTHANDLER__
#define EVENTHANDLER__

#include <allegro5/allegro.h>

enum EventType {_end, _refresh, _next_stage, _back, _normal, _turn_left, _turn_right, _turn_up, _turn_down};

extern ALLEGRO_EVENT *event;
extern ALLEGRO_EVENT_QUEUE *queue;

void eventHandlerInit(ALLEGRO_DISPLAY *display);
EventType getEvent();
bool eventHandler(EventType event);
void stageReset(int stage);
void isNextStage();

#endif // !EVENTHANDLER__

