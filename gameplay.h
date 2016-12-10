#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include "utility.h"
#include "events.h"

typedef struct Object
{
    Object() : _velocity(Vector2f()), _aabb(AABBf()) {}
    Object(Vector2f velocity, AABBf aabb) : _velocity(velocity), _aabb(aabb) {}
    Controller controller;
    Color color;
    bool playable;
    void setVelocity(Vector2f velocity);
    Vector2f getVelocity();
    void setAABB(AABBf aabb);
    AABBf getAABB();
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
    private:
        AABBf _aabb;
        Vector2f _velocity;
} Object;

typedef struct Level
{
    Level();
    std::vector<Object> objects;
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
