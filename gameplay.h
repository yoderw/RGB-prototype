#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include "utility.h"
#include "events.h"

typedef struct Object
{
    Object(Vector2i size, Vector2i tilePos) : _size(size), _tilePos(tilePos), _nextTilePos(tilePos), _interpolating(false), _interpolation(0.0), _interpolationTimer(0.0) {}
    Object() : Object(Vector2i(), Vector2i()) {}
    Controller controller;
    Color color;
    bool playable;
    void setSize(Vector2i size);
    Vector2i getSize();
    void setTilePos(Vector2i tilePos);
    Vector2i getTilePos();
    Vector2i getNextTilePos();
    double getInterpolation();
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
    protected:
        void _goLeft();
        void _goRight();
        void _goUp();
        void _goDown();
    private:
        Vector2i _size;
        Vector2i _tilePos;
        Vector2i _nextTilePos;
        bool _interpolating;
        double _interpolation;
        double _interpolationTimer;
} Object;

typedef struct TestObject : public Object
{
    TestObject(Vector2i size, Vector2i tilePos) : Object(size, tilePos) {}
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
} TestObject;

typedef struct Level
{
    Level();
    std::vector<Object *> objects;
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
    Object getObjectAtIndex(size_t index);
    size_t nObjects();
    int getTileAtIndex(Vector2i index);
    Vector2i getSize();
    private:
        Vector2i _size;
        int **_levelData;
} Level;

typedef struct TestLevel : public Level
{
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
} TestLevel;

#endif /* __GAMEPLAY_H__ */
