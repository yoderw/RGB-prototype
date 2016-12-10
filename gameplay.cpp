#include <iostream>
#include "gameplay.h"
#include "constants.h"

static const int STATIC_LEVEL_W = 32;
static const int STATIC_LEVEL_H = 24;
static int STATIC_LEVEL[STATIC_LEVEL_H][STATIC_LEVEL_W] = {
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

static const int DEFAULT_OBJECT_SPEED = 40;

void Object::setVelocity(Vector2f velocity)
{
    _velocity = velocity;
}

Vector2f Object::getVelocity()
{
    return _velocity;
}

void Object::setAABB(AABBf aabb)
{
    _aabb = aabb;
}

AABBf Object::getAABB()
{
    return _aabb;
}

void Object::init()
{
    std::cout << "Object Init" << std::endl;
}

void Object::update(double dt)
{
    std::cout << "Object Update" << std::endl;
    if (controller.left == controller.right) _velocity.x = 0;
    else
    {
        if (controller.left) _velocity.x = -DEFAULT_OBJECT_SPEED;
        if (controller.right) _velocity.x = DEFAULT_OBJECT_SPEED;
    }
    if (controller.up == controller.down) _velocity.y = 0;
    else
    {
        if (controller.up) _velocity.y = -DEFAULT_OBJECT_SPEED;
        if (controller.down) _velocity.y = DEFAULT_OBJECT_SPEED;
    }

    _aabb.center.x += _velocity.x * dt;
    _aabb.center.y += _velocity.y * dt;
}

void Object::deinit()
{
    std::cout << "Object Deinit" << std::endl;
}

Level::Level()
{
    _size = Vector2i(STATIC_LEVEL_W, STATIC_LEVEL_H);
    _levelData = (int **)malloc(sizeof(int *) * _size.y);
    for (int y = 0; y < _size.y; y++)
    {
        _levelData[y] = (int *)malloc(sizeof(int) * _size.x);
        for (int x = 0; x < _size.x; x++)
        {
            _levelData[y][x] = STATIC_LEVEL[y][x];
        }
    }
}

void Level::init()
{
    std::cout << "Level Init" << std::endl;
}

void Level::update(double dt)
{
    std::cout << "Level Update" << std::endl;
    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object &object = objects[objectIndex];
        if (object.playable) Events::updateController(object.controller);
        object.update(dt);
    }
}

void Level::deinit()
{
    std::cout << "Level Deinit" << std::endl;
}

Object Level::getObjectAtIndex(size_t index)
{
    if (index >= objects.size()) return Object();
    return objects[index];
}

size_t Level::nObjects()
{
    return objects.size();
}

int Level::getTileAtIndex(Vector2i index)
{
    if (index.x >= _size.x || index.y < 0 || index.y >= _size.y || index.y < 0) return -1;
    return _levelData[index.y][index.x];
}

Vector2i Level::getSize()
{
    return _size;
}

void TestLevel::init()
{
    Level::init();

    AABBf aabb(Vector2f(100, 100), Vector2f(32, 32));
    Object playerObject(Vector2f(), aabb);
    playerObject.playable = true;
    playerObject.color = Color(255, 255, 255);
    objects.push_back(playerObject);

    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object &object = objects[objectIndex];
        object.init();
    }
}

void TestLevel::update(double dt)
{
    Level::update(dt);
}

void TestLevel::deinit()
{
    Level::deinit();

    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object &object = objects[objectIndex];
        object.deinit();
    }
}
