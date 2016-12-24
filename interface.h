#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <vector>
#include "utility.h"
#include "events.h"

typedef int InterfaceId;

typedef enum InterfaceType
{
    InterfaceType_Full,
    InterfaceType_Box,
    InterfaceType_Label,
    InterfaceType_Button,
} InterfaceType;

typedef struct Interface
{
    Interface(Color bgColor, InterfaceType type) : _bgColor(bgColor), _type(type) {}
    Interface(InterfaceType type) : Interface(Color(0, 0, 0, 255), type) {}
    Interface(Color bgColor) : Interface(bgColor, InterfaceType_Full) {}
    Interface() : Interface(InterfaceType_Full) {}
    InterfaceId add(Interface *element);
    void remove(InterfaceId id);
    Interface *get(InterfaceId id);
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
    int getCount() { return _elements.size(); }
    void setInterfaceType(InterfaceType type) { _type = type; }
    InterfaceType getInterfaceType() { return _type; }
    void setSize(Vector2i size) { _aabb.size = size; }
    Vector2i getSize() { return _aabb.size; }
    void setPosition(Vector2i position) { _aabb.center = position; }
    Vector2i getPosition() { return _aabb.center; }
    void setAABB(AABBi aabb) { _aabb = aabb; }
    AABBi getAABB() { return _aabb; }
    void setBackgroundColor(Color bgColor) { _bgColor = bgColor; }
    Color getBackgroundColor() { return _bgColor; }
    private:
        std::vector<Interface *> _elements;
        InterfaceType _type;
        AABBi _aabb;
        Color _bgColor;
} Interface;

typedef struct InterfaceBox : public Interface
{
    InterfaceBox(AABBi aabb);
    InterfaceBox() : Interface(InterfaceType_Box) {}
    virtual void init();
} InterfaceBox;

typedef struct InterfaceLabel : public Interface
{
    InterfaceLabel() : Interface(InterfaceType_Label) {}
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
} InterfaceLabel;

typedef enum ButtonState
{
    ButtonState_None,
    ButtonState_Hover,
    ButtonState_Pressed,
} ButtonState;

static const Color BUTTON_COLOR_NONE = Color(0, 0, 0, 255);
static const Color BUTTON_COLOR_HOVER = Color(100, 100, 100, 255);
static const Color BUTTON_COLOR_PRESSED = Color(255, 255, 255, 255);

typedef struct InterfaceButton : public Interface
{
    InterfaceButton() : Interface(InterfaceType_Button), _state(ButtonState_None), _noneColor(BUTTON_COLOR_NONE), _hoverColor(BUTTON_COLOR_HOVER), _pressedColor(BUTTON_COLOR_PRESSED) {}
    virtual void init();
    virtual void update(double dt);
    virtual void deinit();
    void setNoneColor(Color color) { _noneColor = color; }
    void setHoverColor(Color color) { _hoverColor = color; }
    void setPressedColor(Color color) { _pressedColor = color; }
    bool justPressed();
    ButtonState getState() { return _state; }
    private:
        ButtonState _state;
        ButtonState _lastState;
        Color _noneColor;
        Color _hoverColor;
        Color _pressedColor;
} InterfaceButton;

#endif /* __INTERFACE_H__ */
