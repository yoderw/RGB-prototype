#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include <vector>
#include "utility.h"

typedef struct Controller
{
    Controller() : left(false), right(false), up(false), down(false) {}
    bool left, right, up, down;
} Controller;

typedef struct Object
{
    Controller controller;
    AABBi aabb;
    Color color;
    bool playable;
    virtual void init();
    virtual void update();
    virtual void deinit();
} Object;

typedef struct Level
{
    Level();
    std::vector<Object> objects;
    virtual void init();
    virtual void update();
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
    virtual void update();
    virtual void deinit();
} TestLevel;

#endif /* __GAMEPLAY_H__ */
