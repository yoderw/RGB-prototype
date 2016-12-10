#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>

typedef struct Vector2i
{
    Vector2i() : x(0), y(0) {}
    Vector2i(int x, int y) : x(x), y(y) {}
    bool equals(Vector2i other);
    int x, y;
} Vector2i;

typedef struct Vector2f
{
    Vector2f() : x(0), y(0) {}
    Vector2f(float x, float y) : x(x), y(y) {}
    bool equals(Vector2f other);
    float x, y;
} Vector2f;

typedef struct AABBi
{
    AABBi() : center(Vector2i()), size(Vector2i()) {}
    AABBi(Vector2i center, Vector2i size) : center(center), size(size) {}
    Vector2i center, size;
    bool intersects(AABBi other);
} AABBi;

typedef struct AABBf
{
    AABBf() : center(Vector2f()), size(Vector2f()) {}
    AABBf(Vector2f center, Vector2f size) : center(center), size(size) {}
    Vector2f center, size;
    bool intersects(AABBf other);
} AABBf;

typedef struct Color
{
    Color() : r(0), g(0), b(0) {}
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    uint8_t r, g, b;
} Color;

namespace Utility
{
    bool doubleCloseToDouble(double d1, double d2, double epsilon);
}

#endif /* __UTILITY_H__ */
