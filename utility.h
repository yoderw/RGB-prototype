#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>

typedef struct Vector2i
{
    Vector2i() : x(0), y(0) {}
    Vector2i(int x, int y) : x(x), y(y) {}
    int x, y;
} Vector2i;

typedef struct AABBi
{
    AABBi() : center(Vector2i()), size(Vector2i()) {}
    Vector2i center, size;
    bool intersects(AABBi other);
} AABBi;

typedef struct Color
{
    Color() : r(0), g(0), b(0) {}
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    uint8_t r, g, b;
} Color;

#endif /* __UTILITY_H__ */
