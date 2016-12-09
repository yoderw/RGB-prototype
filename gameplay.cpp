#include <iostream>
#include "gameplay.h"

void Level::init()
{
    std::cout << "Level Initialized" << std::endl;
}

void Level::update()
{
    std::cout << "Level Updated" << std::endl;
}

void Level::deinit()
{
    std::cout << "Level Deinitialized" << std::endl;
}

void TestLevel::init()
{
    Level::init();
}

void TestLevel::update()
{
    Level::update();
}

void TestLevel::deinit()
{
    Level::deinit();
}
