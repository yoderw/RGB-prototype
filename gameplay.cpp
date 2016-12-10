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

static const double DEFAULT_TILES_PER_SECOND = 0.2;

void Object::setSize(Vector2i size)
{
    _size = size;
}

Vector2i Object::getSize()
{
    return _size;
}

void Object::setTilePos(Vector2i tilePos)
{
    _tilePos = tilePos;
}

Vector2i Object::getTilePos()
{
    return _tilePos;
}

Vector2i Object::getNextTilePos()
{
    return _nextTilePos;
}

double Object::getInterpolation()
{
    return _interpolation;
}

void Object::init()
{
}

void Object::update(double dt)
{
    _interpolating = !_tilePos.equals(_nextTilePos);
    if (_interpolating)
    {
        _interpolationTimer += dt;
        _interpolation = _interpolationTimer / DEFAULT_TILES_PER_SECOND;
        if (_interpolation >= 1.0)
        {
            _interpolation = 0.0;
            _interpolationTimer = 0.0;
            _tilePos = _nextTilePos;
        }
    }
}

void Object::deinit()
{
}

void Object::_goLeft()
{
    if (_interpolating) return;
    _nextTilePos.x--;
}

void Object::_goRight()
{
    if (_interpolating) return;
    _nextTilePos.x++;
}

void Object::_goUp()
{
    if (_interpolating) return;
    _nextTilePos.y--;
}

void Object::_goDown()
{
    if (_interpolating) return;
    _nextTilePos.y++;
}

void TestObject::init()
{
    Object::init();
    playable = true;
    color = Color(255, 255, 255);
}

void TestObject::update(double dt)
{
    Object::update(dt);
    if (controller.left) _goLeft();
    if (controller.right) _goRight();
    if (controller.up) _goUp();
    if (controller.down) _goDown();
}

void TestObject::deinit()
{
    Object::deinit();
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
}

void Level::update(double dt)
{
    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object *object = objects[objectIndex];
        if (object->playable) Events::updateController(object->controller);
        object->update(dt);
    }
}

void Level::deinit()
{
}

Object Level::getObjectAtIndex(size_t index)
{
    if (index >= objects.size()) return Object();
    return *objects[index];
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
    TestObject *playerObject = new TestObject(Vector2i(TILE_SIZE, TILE_SIZE), Vector2i(10, 10));
    objects.push_back(playerObject);

    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object *object = objects[objectIndex];
        object->init();
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
        Object *object = objects[objectIndex];
        object->deinit();
    }
}
