#include "state.h"

void StateMachine::init()
{
    _currentLevel->init();
}

void StateMachine::update(double dt)
{
    if (_currentLevel->getNextLevelType() != _currentLevel->getLevelType())
    {
        LevelType type = _currentLevel->getNextLevelType();
        _currentLevel->deinit();
        delete _currentLevel;
        _currentLevel = _newLevelForType(type);
        _currentLevel->init();
    }

    _currentLevel->update(dt);
}

void StateMachine::deinit()
{
    _currentLevel->deinit();
}

Level *StateMachine::_newLevelForType(LevelType type)
{
    switch (type)
    {
        case LevelType_Open: return new OpenLevel(); break;
        case LevelType_Test: return new TestLevel(); break;
        case LevelType_Edit: return new EditLevel(); break;
        default: return NULL;
    }
}
