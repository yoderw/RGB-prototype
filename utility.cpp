#include "utility.h"

#include <math.h>

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
