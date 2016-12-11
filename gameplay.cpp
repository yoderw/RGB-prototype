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
static int STATIC_LEVEL_MASK[STATIC_LEVEL_H][STATIC_LEVEL_W] = {
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

static CollisionResponse *COLLISION_MATRIX[ObjectType_Count][ObjectType_Count] = {
    { new CollisionResponse(false, NULL), new CollisionResponse(false, NULL), new CollisionResponse(false, NULL) },
    { new CollisionResponse(false, NULL), new CollisionResponse(false, NULL), new CollisionResponse(true, NULL) },
    { new CollisionResponse(false, NULL), new CollisionResponse(true, NULL), new CollisionResponse(false, NULL) },
};

static const double DEFAULT_TILES_PER_SECOND = 0.08;

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

void Object::resetNextTilePos()
{
    _nextTilePos = _tilePos;
}

Vector2i Object::getNextTilePos()
{
    return _nextTilePos;
}

double Object::getInterpolation()
{
    return _interpolation;
}

bool Object::isInterpolating()
{
    return _interpolating;
}

ObjectType Object::getType()
{
    return _type;
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
    if (controller.left && !(controller.down || controller.up)) _goLeft();
    if (controller.right && !(controller.down || controller.up)) _goRight();
    if (controller.up && !(controller.left || controller.right)) _goUp();
    if (controller.down && !(controller.left || controller.right)) _goDown();
}

void TestObject::deinit()
{
    Object::deinit();
}

void TestCrate::init()
{
    color = Color(0, 255, 0);
}

void TestCrate::update(double dt)
{
}

void TestCrate::deinit()
{
}

Level::Level()
{
    _size = Vector2i(STATIC_LEVEL_W, STATIC_LEVEL_H);
    _levelData = (int **)malloc(sizeof(int *) * _size.y);
    _maskData = (int **)malloc(sizeof(int *) * _size.y);
    for (int y = 0; y < _size.y; y++)
    {
        _levelData[y] = (int *)malloc(sizeof(int) * _size.x);
        _maskData[y] = (int *)malloc(sizeof(int) * _size.x);
        for (int x = 0; x < _size.x; x++)
        {
            _levelData[y][x] = STATIC_LEVEL[y][x];
            _maskData[y][x] = STATIC_LEVEL_MASK[y][x];
        }
    }
}

Level::~Level()
{
    for (int y = 0; y < _size.y; y++)
    {
        free(_levelData[y]);
        free(_maskData[y]);
    }
    free(_levelData);
    free(_maskData);
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

        if (getMaskAtIndex(object->getNextTilePos()))
        {
            object->resetNextTilePos();
        }
    }

    for (int objectIndex1 = 0; objectIndex1 < objects.size(); objectIndex1++)
    {
        for (int objectIndex2 = objectIndex1; objectIndex2 < objects.size(); objectIndex2++)
        {
            Object *object1 = objects[objectIndex1];
            Object *object2 = objects[objectIndex2];
            if (object1 == object2) continue;
            ObjectType type1 = object1->getType();
            ObjectType type2 = object2->getType();
            CollisionResponse *response = COLLISION_MATRIX[type1][type2];
            if (response)
            {
                if (response->shouldCollide)
                {
                    if (object1->getNextTilePos().equals(object2->getTilePos()))
                    {
                        object1->resetNextTilePos();
                    }
                    if (object2->getNextTilePos().equals(object1->getTilePos()))
                    {
                        object2->resetNextTilePos();
                    }
                }
                if (response->callback)
                {
                    //response->callback(object1, object2);
                }
            }
        }
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

int Level::getMaskAtIndex(Vector2i index)
{
    if (index.x >= _size.x || index.y < 0 || index.y >= _size.y || index.y < 0) return -1;
    return _maskData[index.y][index.x];
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
    TestCrate *crateObject = new TestCrate();
    objects.push_back(crateObject);

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
