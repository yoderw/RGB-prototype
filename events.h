#ifndef __EVENTS_H__
#define __EVENTS_H__

// I hate that I'm doing this.
#include <SDL2/SDL.h>

typedef SDL_Keycode Keycode;

typedef struct Keyboard
{
    int size;
    const uint8_t *lastKeyState;
    const uint8_t *keyState;
    void init();
    void update();
    void deinit();
} Keyboard;

typedef struct Controller
{
    Controller() : left(false), right(false), up(false), down(false) {}
    bool left, right, up, down;
} Controller;

namespace Events
{
    void updateController(Controller &controller);
    bool keyIsUp(Keycode code);
    bool keyIsDown(Keycode code);
    bool process();
    void init();
    void update();
    void deinit();
}

#endif /* __EVENTS_H__ */
