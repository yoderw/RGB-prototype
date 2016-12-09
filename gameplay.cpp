#include <iostream>
#include "gameplay.h"

void Object::init()
{
    std::cout << "Object Init" << std::endl;
}

void Object::update()
{
    std::cout << "Object Update" << std::endl;
}

void Object::deinit()
{
    std::cout << "Object Deinit" << std::endl;
}

void Level::init()
{
    std::cout << "Level Init" << std::endl;
}

void Level::update()
{
    std::cout << "Level Update" << std::endl;
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

void TestLevel::init()
{
    Level::init();

    Object playerObject;
    playerObject.playable = true;
    playerObject.aabb.size.x = 32;
    playerObject.aabb.size.y = 32;
    playerObject.aabb.center.x = 100;
    playerObject.aabb.center.y = 100;
    playerObject.color = Color(255, 255, 255);
    objects.push_back(playerObject);

    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object &object = objects[objectIndex];
        object.init();
    }
}

void TestLevel::update()
{
    Level::update();

    for (int objectIndex = 0; objectIndex < objects.size(); objectIndex++)
    {
        Object &object = objects[objectIndex];
        object.update();
    }
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
