#include "utility.h"

#include <math.h>

bool Vector2i::equals(Vector2i other)
{
    return x == other.x && y == other.y;
}

bool Vector2f::equals(Vector2f other)
{
    return x == other.x && y == other.y;
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
