#include <iostream>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "utility.h"
#include "gameplay.h"
#include "constants.h"
#include "events.h"

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

static void setFillColorForTileId(SDL_Renderer *renderer, int tileId)
{
    Color color;
    if (tileId >= 0 && tileId < N_COLORS) color = COLORS[tileId];
    else color = Color(0, 0, 0);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
}

static void renderLevel(SDL_Renderer *renderer)
{
    SDL_Rect baseRect;
    baseRect.w = TILE_SIZE;
    baseRect.h = TILE_SIZE;
    Vector2i size = globalLevel->getSize();
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            baseRect.x = x * TILE_SIZE;
            baseRect.y = y * TILE_SIZE;
            int tileId = globalLevel->getTileAtIndex(Vector2i(x, y));
            setFillColorForTileId(renderer, tileId);
            SDL_RenderFillRect(renderer, &baseRect);
        }
    }
}

static void init()
{
    Events::init();
    globalLevel->init();
}

static void update(double dt)
{
    Events::update();
    globalLevel->update(dt);
}

static void deinit()
{
    Events::deinit();
    globalLevel->deinit();
}

static void renderObject(SDL_Renderer *renderer, Object object)
{
    SDL_Rect rect;
    AABBf aabb = object.getAABB();
    rect.x = aabb.center.x - aabb.size.x / 2;
    rect.y = aabb.center.y - aabb.size.y / 2;
    rect.w = aabb.size.x;
    rect.h = aabb.size.y;
    SDL_SetRenderDrawColor(renderer, object.color.r, object.color.g, object.color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

static void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderLevel(renderer);

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

        running = Events::process();

        while (lag >= MS_PER_UPDATE)
        {
            update(elapsed / 1000.0);
            lag -= MS_PER_UPDATE;
        }

        render(renderer);
    }

    deinit();
    SDL_Quit();

    return 0;
}
