#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>

#define CAST(static_type, to_cast) ((static_type)to_cast)

typedef struct Vector2i
{
    Vector2i() : x(0), y(0) {}
    Vector2i(int x, int y) : x(x), y(y) {}
    bool equals(Vector2i other);
    Vector2i add(Vector2i other);
    Vector2i minus(Vector2i other);
    Vector2i multiply(Vector2i other);
    Vector2i multiply(double scalar);
    int x, y;
} Vector2i;

typedef struct Vector2f
{
    Vector2f() : x(0), y(0) {}
    Vector2f(float x, float y) : x(x), y(y) {}
    bool equals(Vector2f other);
    Vector2f lerp(Vector2f other, double interp);
    Vector2f add(Vector2f other);
    Vector2f minus(Vector2f other);
    Vector2f multiply(Vector2f other);
    Vector2f multiply(double scalar);
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
    Color() : r(0), g(0), b(0), a(0) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
    bool equals(Color other);
    uint8_t r, g, b, a;
} Color;

namespace Utility
{
    bool doubleCloseToDouble(double d1, double d2, double epsilon);
}

#endif /* __UTILITY_H__ */
