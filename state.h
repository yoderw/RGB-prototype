#ifndef __STATE_H__
#define __STATE_H__

#include "gameplay.h"

typedef struct StateMachine
{
    StateMachine() : _currentLevel(new OpenLevel()) {}
    void init();
    void update(double dt);
    void deinit();
    Level *getLevel() { return _currentLevel; }
    private:
        Level *_currentLevel;
        Level *_newLevelForType(LevelType type);
} StateMachine;

#endif /* __STATE_H__ */
