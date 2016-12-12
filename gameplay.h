#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include "utility.h"
#include "events.h"

typedef enum ObjectType
{
    ObjectType_None = 0,
    ObjectType_Player,
    ObjectType_Crate,
    ObjectType_Count,
} ObjectType;

typedef struct Object
{
    Object(Vector2i size, Vector2i tilePos, Color color,  ObjectType type) : _size(size), _tilePos(tilePos), _nextTilePos(tilePos), _interpolating(false), _interpolation(0.0), _interpolationTimer(0.0), _type(type), color(color) {}
    Object() : Object(Vector2i(), Vector2i(), Color(255, 255, 255, 255), ObjectType_None) {}
    Controller controller;
    Color color;
    bool playable;
    void setSize(Vector2i size);
    Vector2i getSize();
    void setTilePos(Vector2i tilePos);
    Vector2i getTilePos();
    void resetNextTilePos();
    Vector2i getNextTilePos();
    double getInterpolation();
    bool isInterpolating();
    ObjectType getType();
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    void move(Vector2i nextPos);
    private:
        ObjectType _type;
        Vector2i _size;
        Vector2i _tilePos;
        Vector2i _nextTilePos;
        bool _interpolating;
        double _interpolation;
        double _interpolationTimer;
} Object;

typedef struct TestObject : public Object
{
    TestObject(Vector2i size, Vector2i tilePos) : Object(size, tilePos, Color(0, 0, 0, 255), ObjectType_Player) {}
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
} TestObject;

typedef struct TestCrate : public Object
{
    TestCrate(Vector2i position, Color color) : Object(Vector2i(32, 32), position, color, ObjectType_Crate) {}
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
} TestCrate;

typedef struct Level
{
    Level();
    ~Level();
    std::vector<Object *> objects;
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
    Object getObjectAtIndex(size_t index);
    size_t nObjects();
    int getTileAtIndex(Vector2i index);
    int getMaskAtIndex(Vector2i index);
    Vector2i getSize();
    private:
        Vector2i _size;
        int **_levelData;
        int **_maskData;
} Level;

typedef struct TestLevel : public Level
{
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
} TestLevel;

typedef void (*CollisionCallback)(Object *o1, Object *o2);

typedef struct CollisionResponse
{
    CollisionResponse(bool shouldCollide, CollisionCallback callback) : shouldCollide(shouldCollide), callback(callback) {}
    CollisionCallback callback;
    bool shouldCollide;
} CollisionResponse;

#endif /* __GAMEPLAY_H__ */
