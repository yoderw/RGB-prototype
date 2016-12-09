#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include <vector>

typedef struct Controller
{
    Controller() : left(false), right(false), up(false), down(false) {}
    bool left, right, up, down;
} Controller;

typedef struct Object
{
    Controller controller;
    bool playable;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void deinit() = 0;
} Object;

typedef struct Level
{
    std::vector<Object> objects;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void deinit() = 0;
} Level;

#endif /* __GAMEPLAY_H__ */
