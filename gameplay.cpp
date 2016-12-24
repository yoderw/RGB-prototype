#include <iostream>
#include <json.hpp>
#include "gameplay.h"
#include "constants.h"

using json = nlohmann::json;

static const int STATIC_LEVEL_W = 32;
static const int STATIC_LEVEL_H = 24;
static int STATIC_LEVEL[STATIC_LEVEL_H][STATIC_LEVEL_W] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
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
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
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

void playerCrateCollision(Object *o1, Object *o2)
{
    TestObject *player;
    TestCrate *crate;
    if (o1->getType() == ObjectType_Player)
    {
        player = (TestObject *)o1;
        crate = (TestCrate *)o2;
    }
    else
    {
        player = (TestObject *)o2;
        crate = (TestCrate *)o1;
    }

    Vector2i dir = player->getTilePos().minus(crate->getTilePos()).multiply(-1);
    crate->move(dir);
}

void crateCrateCollision(Object *o1, Object *o2)
{
    TestCrate *crate1 = (TestCrate *)o1;
    TestCrate *crate2 = (TestCrate *)o2;
}

static CollisionResponse *COLLISION_MATRIX[ObjectType_Count][ObjectType_Count] = {
    { new CollisionResponse(false, NULL), new CollisionResponse(false, NULL), new CollisionResponse(false, NULL) },
    { new CollisionResponse(false, NULL), new CollisionResponse(false, NULL), new CollisionResponse(true, playerCrateCollision) },
    { new CollisionResponse(false, NULL), new CollisionResponse(true, playerCrateCollision), new CollisionResponse(false, crateCrateCollision) },
};

static const double DEFAULT_TILES_PER_SECOND = 0.12;

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

void Object::goLeft()
{
    if (_interpolating) return;
    _nextTilePos.x--;
}

void Object::goRight()
{
    if (_interpolating) return;
    _nextTilePos.x++;
}

void Object::goUp()
{
    if (_interpolating) return;
    _nextTilePos.y--;
}

void Object::goDown()
{
    if (_interpolating) return;
    _nextTilePos.y++;
}

void Object::move(Vector2i nextPos)
{
    _nextTilePos = _nextTilePos.add(nextPos);
}

void TestObject::init()
{
    Object::init();
    playable = true;
}

void TestObject::update(double dt)
{
    Object::update(dt);
    if (controller.left && !(controller.down || controller.up)) goLeft();
    if (controller.right && !(controller.down || controller.up)) goRight();
    if (controller.up && !(controller.left || controller.right)) goUp();
    if (controller.down && !(controller.left || controller.right)) goDown();
}

void TestObject::deinit()
{
    Object::deinit();
}

void TestCrate::init()
{
    Object::init();
}

void TestCrate::update(double dt)
{
    Object::update(dt);
}

void TestCrate::deinit()
{
    Object::deinit();
}

Level::Level(LevelType type) : _levelData(NULL), _maskData(NULL), _type(type), _nextLevelType(type), _interface(new Interface())
{
    _size = Vector2i(STATIC_LEVEL_W, STATIC_LEVEL_H);
    allocateLevelData();
    allocateMaskData();
}

Level::~Level()
{
    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        delete objects[objectIndex];
    }

}

void Level::init()
{
    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object *object = objects[objectIndex];
        object->deinit();
    }

    _interface->init();
}

void Level::update(double dt)
{
    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object *object = objects[objectIndex];
        if (object->playable) Events::updateController(object->controller);
        object->update(dt);
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
                if (response->callback)
                {
                    if (object1->getNextTilePos().equals(object2->getNextTilePos()))
                    {
                        response->callback(object1, object2);
                        // Need to check collision twice.
                        if (getMaskAtIndex(object1->getNextTilePos()))
                        {
                            object1->resetNextTilePos();
                        }
                        if (getMaskAtIndex(object2->getNextTilePos()))
                        {
                            object2->resetNextTilePos();
                        }
                    }
                }
                if (response->shouldCollide)
                {
                    if (object1->getNextTilePos().equals(object2->getNextTilePos()))
                    {
                        object1->resetNextTilePos();
                    }
                }
            }
        }
    }

    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object *object = objects[objectIndex];
        if (getMaskAtIndex(object->getNextTilePos()))
        {
            object->resetNextTilePos();
        }
    }

    _interface->update(dt);
}

void Level::deinit()
{
    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object *object = objects[objectIndex];
        object->deinit();
    }

    _interface->deinit();
}

Object Level::getObjectAtIndex(size_t index)
{
    if (index >= objects.size()) return Object();
    return *objects[index];
}

void Level::setTileAtIndex(Vector2i index, int tile)
{
    if (index.x >= _size.x || index.y < 0 || index.y >= _size.y || index.y < 0) return;
    _levelData[index.y][index.x] = tile;
}

void Level::setMaskAtIndex(Vector2i index, int mask)
{
    if (index.x >= _size.x || index.y < 0 || index.y >= _size.y || index.y < 0) return;
    _maskData[index.y][index.x] = mask;
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

void Level::loadFromFile(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (!file)
    {
        std::cout << "Unable to open file at \'" << path << "\'" << std::endl;
        std::cout << "Making new file" << std::endl;
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char *fileData = (char *)malloc(sizeof(char) * fileSize);

    if (fread(fileData, sizeof(char), fileSize, file) != fileSize)
    {
        std::cout << "Unable to read whole file at \'" << path << "\'" << std::endl;
        std::cout << "Don't know what to do so crashing" << std::endl;
        exit(-1);
    }

    std::cout << "rawFileData: ";
    for (size_t dataIndex = 0; dataIndex < fileSize; dataIndex++)
    {
        std::cout << fileData[dataIndex];
    }

    std::cout << "fileData: " << fileData << std::endl;
    auto jsonObject = json::parse(fileData);
}

void Level::clearLevelData()
{
    for (int y = 0; y < getSize().y; y++)
    {
        for (int x = 0; x < getSize().x; x++)
        {
            _levelData[y][x] = 0;
            _maskData[y][x] = 0;
        }
    }
}

void Level::freeLevelData()
{
    if (_levelData)
    {
        for (int y = 0; y < _size.y; y++)
        {
            if (_levelData[y])
            {
                free(_levelData[y]);
                _levelData[y] = NULL;
            }
        }
        free(_levelData);
        _levelData = NULL;
    }

    if (_maskData)
    {
        for (int y = 0; y < _size.y; y++)
        {
            if (_maskData[y])
            {
                free(_maskData[y]);
                _maskData[y] = NULL;
            }
        }
        free(_maskData);
        _maskData = NULL;
    }
}

void Level::allocateLevelData()
{
    if (!_levelData)
    {
        _levelData = (int **)malloc(sizeof(int *) * _size.y);
        for (int y = 0; y < _size.y; y++)
        {
            _levelData[y] = (int *)malloc(sizeof(int) * _size.x);
        }
    }
}

void Level::allocateMaskData()
{
    if (!_maskData)
    {
        _maskData = (int **)malloc(sizeof(int *) * _size.y);
        for (int y = 0; y < _size.y; y++)
        {
            _maskData[y] = (int *)malloc(sizeof(int) * _size.x);
        }
    }
}

void OpenLevel::init()
{
    Level::init();
    setNextLevelType(LevelType_Edit);
}

InterfaceId mouseBoxId;

void EditLevel::init()
{
    Level::init();
    clearLevelData();
    Vector2i mousePos = Events::getMousePosition();
    int mouseTileX = (mousePos.x / TILE_SIZE) * TILE_SIZE;
    int mouseTileY = (mousePos.y / TILE_SIZE) * TILE_SIZE;
    Vector2i mouseTilePos = Vector2i(mouseTileX, mouseTileY);
    AABBi mouseBoxBox = AABBi(mouseTilePos, Vector2i(TILE_SIZE, TILE_SIZE));
    InterfaceBox *mouseBox = new InterfaceBox(mouseBoxBox);
    mouseBox->setBackgroundColor(Color(100, 100, 100, 100));
    mouseBoxId = getInterface()->add(mouseBox);

    TestObject *playerObject = new TestObject(Vector2i(TILE_SIZE, TILE_SIZE), Vector2i(10, 10));
    objects.push_back(playerObject);
}

void EditLevel::update(double dt)
{
    Level::update(dt);
    Vector2i mousePos = Events::getMousePosition();
    int mouseTileX = (mousePos.x / TILE_SIZE);
    int mouseTileY = (mousePos.y / TILE_SIZE);
    Vector2i boxPos = Vector2i(mouseTileX * TILE_SIZE, mouseTileY * TILE_SIZE);
    getInterface()->get(mouseBoxId)->setPosition(boxPos);

    if (Events::leftButtonIsDown())
    {
        setTileAtIndex(Vector2i(mouseTileX, mouseTileY), 1);
        setMaskAtIndex(Vector2i(mouseTileX, mouseTileY), 1);
    }

    if (Events::rightButtonIsDown())
    {
        setTileAtIndex(Vector2i(mouseTileX, mouseTileY), 0);
        setMaskAtIndex(Vector2i(mouseTileX, mouseTileY), 0);
    }
}

void EditLevel::deinit()
{
    Level::deinit();
}

InterfaceId button1;

void TestLevel::init()
{
    Level::init();
    loadFromFile("test.json");
    TestObject *playerObject = new TestObject(Vector2i(TILE_SIZE, TILE_SIZE), Vector2i(10, 10));
    objects.push_back(playerObject);
    objects.push_back(new TestCrate(Vector2i(5, 5), Color(255, 255, 0, 200)));
    objects.push_back(new TestCrate(Vector2i(6, 8), Color(255, 0, 0, 200)));
    objects.push_back(new TestCrate(Vector2i(6, 8), Color(0, 0, 255, 200)));

    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object *object = objects[objectIndex];
        object->init();
    }

    Interface *interface = getInterface();
    button1 = interface->add(new InterfaceButton());
    interface->get(button1)->setSize(Vector2i(32, 32));
    interface->get(button1)->setPosition(Vector2i(100, 100));
}

void TestLevel::update(double dt)
{
    Level::update(dt);
    Interface *inter = getInterface();
    if (CAST(InterfaceButton *, inter->get(button1))->justPressed())
    {
        printf("CONASDKNOASD\n");
    }
}

void TestLevel::deinit()
{
    Level::deinit();
}
