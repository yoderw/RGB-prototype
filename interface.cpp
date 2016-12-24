#include "interface.h"

InterfaceId Interface::add(Interface *element)
{
    _elements.push_back(element);
    return _elements.size() - 1;
}

void Interface::remove(InterfaceId id)
{
    if (id < 0 || id >= _elements.size()) return;
    _elements[id] = _elements[_elements.size() - 1];
    _elements.pop_back();
}

Interface *Interface::get(InterfaceId id)
{
    if (id < 0 || id >= _elements.size()) return NULL;
    return _elements[id];
}

void Interface::init()
{
    for (int interIndex = 0; interIndex < _elements.size(); interIndex++)
    {
        Interface *inter = get(interIndex);
        inter->init();
    }
}

void Interface::update(double dt)
{
    for (int interIndex = 0; interIndex < _elements.size(); interIndex++)
    {
        Interface *inter = get(interIndex);
        inter->update(dt);
    }
}

void Interface::deinit()
{
    for (int interIndex = 0; interIndex < _elements.size(); interIndex++)
    {
        Interface *inter = get(interIndex);
        inter->init();
    }
}

InterfaceBox::InterfaceBox(AABBi aabb) : Interface(InterfaceType_Box)
{
    setAABB(aabb);
}

void InterfaceBox::init()
{
    Interface::init();
}

void InterfaceLabel::init()
{
    Interface::init();
}

void InterfaceLabel::update(double dt)
{
    Interface::update(dt);
}

void InterfaceLabel::deinit()
{
    Interface::deinit();
}

void InterfaceButton::init()
{
    Interface::init();
}

void InterfaceButton::update(double dt)
{
    Interface::update(dt);
    _lastState = _state;
    switch (_state)
    {
        case ButtonState_None:
        {
            setBackgroundColor(_noneColor);
            if (Events::mouseInAABB(getAABB()))
            {
                if (Events::leftButtonIsDown()) _state = ButtonState_Pressed;
                else _state = ButtonState_Hover;
            }
        } break;
        case ButtonState_Hover:
        {
            setBackgroundColor(_hoverColor);
            if (!Events::mouseInAABB(getAABB())) _state = ButtonState_None;
            else if (Events::leftButtonIsDown()) _state = ButtonState_Pressed;
        } break;
        case ButtonState_Pressed:
        {
            setBackgroundColor(_pressedColor);
            if (!Events::mouseInAABB(getAABB())) _state = ButtonState_None;
            else if (!Events::leftButtonIsDown()) _state = ButtonState_Hover;
        } break;
    }
}

void InterfaceButton::deinit()
{
    Interface::deinit();
}

bool InterfaceButton::justPressed()
{
    return _state == ButtonState_Pressed && _lastState != _state;
}

