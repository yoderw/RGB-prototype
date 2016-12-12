#include "utility.h"

#include <math.h>

bool Vector2i::equals(Vector2i other)
{
    return x == other.x && y == other.y;
}

Vector2i Vector2i::add(Vector2i other)
{
    return Vector2i(x + other.x, y + other.y);
}

Vector2i Vector2i::minus(Vector2i other)
{
    return Vector2i(x - other.x, y - other.y);
}

Vector2i Vector2i::multiply(Vector2i other)
{
    return Vector2i(x * other.x, y * other.y);
}

Vector2i Vector2i::multiply(double scalar)
{
    return Vector2i(x * scalar, y * scalar);
}

bool Vector2f::equals(Vector2f other)
{
    return x == other.x && y == other.y;
}

Vector2f Vector2f::add(Vector2f other)
{
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::minus(Vector2f other)
{
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::multiply(Vector2f other)
{
    return Vector2f(x * other.x, y * other.y);
}

Vector2f Vector2f::multiply(double scalar)
{
    return Vector2f(x * scalar, y * scalar);
}

Vector2f Vector2f::lerp(Vector2f other, double interp)
{
    Vector2f newVector;
    newVector.x = x + (other.x - x) * interp;
    newVector.y = y + (other.y - y) * interp;
    return newVector;
}

bool AABBi::intersects(AABBi o)
{
    return center.x < o.center.x + o.size.x &&
        center.x + size.x > o.center.x &&
        center.y < o.center.y + o.size.y &&
        size.y + center.y > o.center.y;
}

bool AABBf::intersects(AABBf o)
{
    return center.x < o.center.x + o.size.x &&
        center.x + size.x > o.center.x &&
        center.y < o.center.y + o.size.y &&
        size.y + center.y > o.center.y;
}

namespace Utility
{
    bool doubleCloseToDouble(double d1, double d2, double epsilon)
    {
        return d1 <= d2 + epsilon && d1 >= d2 - epsilon;
    }
}
