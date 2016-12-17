#include <SDL2/SDL.h>
#include "events.h"

void Keyboard::init()
{
    lastKeyState = SDL_GetKeyboardState(&size);
    keyState = SDL_GetKeyboardState(NULL);
}

void Keyboard::update()
{
    lastKeyState = keyState;
    keyState = SDL_GetKeyboardState(NULL);
}

void Keyboard::deinit() {}

void Mouse::init()
{
    lastState = SDL_GetMouseState(&position.x, &position.y);
    state = SDL_GetMouseState(NULL, NULL);
}

void Mouse::update()
{
    lastState = state;
    state = SDL_GetMouseState(&position.x, &position.y);
}

void Mouse::deinit() {}

namespace Events
{
    static Controller currentController;
    static Keyboard currentKeyboard;
    static Mouse currentMouse;
    static SDL_Event event;

    void updateController(Controller &controller)
    {
        controller = currentController;
    }

    bool keyIsDown(Keycode code)
    {
        SDL_Scancode scancode = SDL_GetScancodeFromKey(code);
        return currentKeyboard.keyState[scancode];
    }

    bool keyWasDown(Keycode code)
    {
        SDL_Scancode scancode = SDL_GetScancodeFromKey(code);
        return currentKeyboard.lastKeyState[scancode];
    }

    bool leftButtonIsDown()
    {
        return currentMouse.state & SDL_BUTTON(SDL_BUTTON_LEFT);
    }

    bool middleButtonIsDown()
    {
        return currentMouse.state & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    }

    bool rightButtonIsDown()
    {
        return currentMouse.state & SDL_BUTTON(SDL_BUTTON_RIGHT);
    }

    bool leftButtonJustDown()
    {
        return !(currentMouse.lastState & SDL_BUTTON(SDL_BUTTON_LEFT)) && leftButtonIsDown();
    }

    bool middleButtonJustDown()
    {
        return !(currentMouse.lastState & SDL_BUTTON(SDL_BUTTON_MIDDLE)) && middleButtonIsDown();
    }

    bool rightButtonJustDown()
    {
        return !(currentMouse.lastState & SDL_BUTTON(SDL_BUTTON_RIGHT)) && rightButtonIsDown();
    }

    bool mouseInAABB(AABBi aabb)
    {
        AABBi mouseAABB = AABBi(Vector2i(currentMouse.position.x, currentMouse.position.y), Vector2i(1, 1));
        return aabb.intersects(mouseAABB);
    }

    bool process()
    {
        bool returnValue = true;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    returnValue = false;
                } break;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT: currentController.left = true; break;
                        case SDLK_RIGHT: currentController.right = true; break;
                        case SDLK_UP: currentController.up = true; break;
                        case SDLK_DOWN: currentController.down = true; break;
                    }
                } break;
                case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT: currentController.left = false; break;
                        case SDLK_RIGHT: currentController.right = false; break;
                        case SDLK_UP: currentController.up = false; break;
                        case SDLK_DOWN: currentController.down = false; break;
                    }
                } break;
            }
        }

        currentKeyboard.update();

        return returnValue;
    }

    void init()
    {
        currentKeyboard.init();
        currentMouse.init();
    }

    void update()
    {
        currentKeyboard.update();
        currentMouse.update();
    }

    void deinit()
    {
        currentKeyboard.deinit();
        currentMouse.deinit();
    }
}
