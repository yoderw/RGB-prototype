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

void Keyboard::deinit()
{
}

namespace Events
{
    static Controller currentController;
    static Keyboard currentKeyboard;
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
    }

    void update()
    {
        currentKeyboard.update();
    }

    void deinit()
    {
        currentKeyboard.deinit();
    }
}
