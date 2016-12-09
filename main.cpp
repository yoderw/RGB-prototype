#include <iostream>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "utility.h"
#include "gameplay.h"

static const int N_COLORS = 5;
static const Color COLORS[N_COLORS] = {
    { 0, 0, 0 },
    { 150, 150, 150 },
    { 255, 0, 0 },
    { 0, 255, 0 },
    { 0, 0, 255 },
};

static const double FPS = 60;
static const double MS_PER_UPDATE = 1000 / FPS;

static const char *WIN_TITLE = "RGB";
static const int WIN_X = SDL_WINDOWPOS_UNDEFINED;
static const int WIN_Y = SDL_WINDOWPOS_UNDEFINED;
static const int WIN_W = 1024;
static const int WIN_H = 768;
static const int WIN_FLAGS = 0;
static const uint32_t REN_FLAGS = SDL_RENDERER_PRESENTVSYNC;

static bool running;
static Controller globalController;
static TestLevel *globalLevel;

static const int LEVEL_W = 32;
static const int LEVEL_H = 24;
static const int TILE_SIZE = 32;
static int STATIC_LEVEL[LEVEL_H][LEVEL_W] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

static void setFillColorForTileId(SDL_Renderer *renderer, int tileId)
{
    Color color;
    if (tileId >= 0 && tileId < N_COLORS) color = COLORS[tileId];
    else color = Color(0, 0, 0);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
}

static void renderLevel(SDL_Renderer *renderer, int level[LEVEL_H][LEVEL_W], Vector2i size)
{
    SDL_Rect baseRect;
    baseRect.w = TILE_SIZE;
    baseRect.h = TILE_SIZE;
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            baseRect.x = x * TILE_SIZE;
            baseRect.y = y * TILE_SIZE;
            int tileId = level[y][x];
            setFillColorForTileId(renderer, tileId);
            SDL_RenderFillRect(renderer, &baseRect);
        }
    }
}

static void init()
{
    globalLevel->init();
}

static void update()
{
    globalLevel->update();
}

static void deinit()
{
    globalLevel->deinit();
}

static void renderObject(SDL_Renderer *renderer, Object object)
{
    SDL_Rect rect;
    rect.x = object.aabb.center.x - object.aabb.size.x / 2;
    rect.y = object.aabb.center.y - object.aabb.size.y / 2;
    rect.w = object.aabb.size.x;
    rect.h = object.aabb.size.y;
    SDL_SetRenderDrawColor(renderer, object.color.r, object.color.g, object.color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

static void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderLevel(renderer, STATIC_LEVEL, Vector2i(LEVEL_W, LEVEL_H));

    for (int objectIndex = 0; objectIndex < globalLevel->nObjects(); objectIndex++)
    {
        Object object = globalLevel->getObjectAtIndex(objectIndex);
        renderObject(renderer, object);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, WIN_FLAGS);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, REN_FLAGS);

    running = true;
    SDL_Event event;

    globalLevel = new TestLevel();
    init();

    double previous = (double)SDL_GetTicks();
    double lag = 0.0;

    while (running)
    {
        double current = (double)SDL_GetTicks();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                {
                    running = false;
                } break;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT: globalController.left = true; break;
                        case SDLK_RIGHT: globalController.right = true; break;
                        case SDLK_UP: globalController.up = true; break;
                        case SDLK_DOWN: globalController.down = true; break;
                    }
                } break;
                case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT: globalController.left = false; break;
                        case SDLK_RIGHT: globalController.right = false; break;
                        case SDLK_UP: globalController.up = false; break;
                        case SDLK_DOWN: globalController.down = false; break;
                    }
                } break;
            }
        }

        while (lag >= MS_PER_UPDATE)
        {
            update();
            lag -= MS_PER_UPDATE;
        }

        render(renderer);
    }

    deinit();
    SDL_Quit();

    return 0;
}
