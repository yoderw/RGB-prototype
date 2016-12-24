#include <iostream>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "utility.h"
#include "gameplay.h"
#include "constants.h"
#include "events.h"
#include "state.h"
#include "interface.h"

static const int N_COLORS = 5;
static const Color COLORS[N_COLORS] = {
    { 255, 255, 255, 255 },
    { 150, 150, 150, 255 },
    { 255, 0, 0, 255 },
    { 0, 255, 0, 255 },
    { 0, 0, 255, 255 },
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

static void setFillColorForTileId(SDL_Renderer *renderer, int tileId)
{
    Color color;
    if (tileId >= 0 && tileId < N_COLORS) color = COLORS[tileId];
    else color = Color(0, 0, 0, 255);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
}

static void renderInterface(SDL_Renderer *renderer, Interface *interface)
{
    SDL_Rect rect;
    for (int interIndex = 0; interIndex < interface->getCount(); interIndex++)
    {
        Interface* inter = interface->get(interIndex);
        Color bgColor = inter->getBackgroundColor();
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        rect.w = inter->getSize().x;
        rect.h = inter->getSize().y;
        rect.x = inter->getPosition().x;
        rect.y = inter->getPosition().y;
        SDL_RenderFillRect(renderer, &rect);
        if (inter->getCount() > 0) renderInterface(renderer, inter);
    }
}

static void renderLevel(Level *level, SDL_Renderer *renderer)
{
    SDL_Rect baseRect;
    baseRect.w = TILE_SIZE;
    baseRect.h = TILE_SIZE;
    Vector2i size = level->getSize();
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            baseRect.x = x * TILE_SIZE;
            baseRect.y = y * TILE_SIZE;
            int tileId = level->getTileAtIndex(Vector2i(x, y));
            setFillColorForTileId(renderer, tileId);
            SDL_RenderFillRect(renderer, &baseRect);
        }
    }
    renderInterface(renderer, level->getInterface());
}

static void renderObject(SDL_Renderer *renderer, Object object)
{
    SDL_Rect rect;
    Color color = object.color;
    Vector2i tilePos = object.getTilePos();
    Vector2i nextTilePos = object.getNextTilePos();
    Vector2i size = object.getSize();
    Vector2f originalPos = Vector2f(tilePos.x * TILE_SIZE, tilePos.y * TILE_SIZE);
    Vector2f nextPos = Vector2f(nextTilePos.x * TILE_SIZE, nextTilePos.y * TILE_SIZE);
    Vector2f newPos = originalPos.lerp(nextPos, object.getInterpolation());
    rect.x = newPos.x + TILE_SIZE / 2 - size.x / 2;
    rect.y = newPos.y + TILE_SIZE / 2 - size.y / 2;
    rect.w = size.x;
    rect.h = size.y;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

static void render(StateMachine *machine, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    Level *level = machine->getLevel();
    renderLevel(level, renderer);

    for (int objectIndex = 0; objectIndex < level->nObjects(); objectIndex++)
    {
        Object object = level->getObjectAtIndex(objectIndex);
        renderObject(renderer, object);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(WIN_TITLE, WIN_X, WIN_Y, WIN_W, WIN_H, WIN_FLAGS);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, REN_FLAGS);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    running = true;
    SDL_Event event;

    StateMachine *machine = new StateMachine();
    Events::init();
    machine->init();

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
            Events::update();
            machine->update(elapsed / 1000.0);
            lag -= MS_PER_UPDATE;
        }

        render(machine, renderer);
    }

    Events::deinit();
    machine->deinit();
    SDL_Quit();

    return 0;
}
