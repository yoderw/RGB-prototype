#ifndef __EVENTS_H__
#define __EVENTS_H__

// I hate that I'm doing this.
#include <SDL2/SDL.h>
#include <stdint.h>
#include "utility.h"

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

typedef struct Mouse
{
    Vector2i position;
    Vector2i lastPosition;
    uint32_t state;
    uint32_t lastState;
    virtual void init();
    virtual void update();
    virtual void deinit();
} Mouse;

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
    bool leftButtonIsDown();
    bool middleButtonIsDown();
    bool rightButtonIsDown();
    bool leftButtonJustDown();
    bool middleButtonJustDown();
    bool rightButtonJustDown();
    bool mouseInAABB(AABBi aabb);
    bool process();
    void init();
    void update();
    void deinit();
}

#endif /* __EVENTS_H__ */
