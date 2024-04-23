#ifndef STDINT_H_
#define STDINT_H_
#include <stdint.h>
#endif

#include "LUTtrig.h"
#ifndef VECTOR_H_
#define VECTOR_H_

class FPVector2D
{
public:
    int32_t x, y;

    FPVector2D(void) : x(0), y(0) {}
    FPVector2D(int32_t xx, int32_t yy) : x(xx), y(yy) {}

    // Arithmetic operators
    FPVector2D operator+(const FPVector2D &other) const {
        return FPVector2D(x + other.x, y + other.y);
    }
    FPVector2D operator-(const FPVector2D &other) const {
        return FPVector2D(x - other.x, y - other.y);
    }
    FPVector2D operator*(int16_t s) const {
        return FPVector2D(x * s, y * s);
    }
    FPVector2D operator/(int16_t s) const {
        return FPVector2D(x / s, y / s);
    }
    FPVector2D operator>>(int16_t s) const {
        return FPVector2D(x >> s, y >> s);
    }
    FPVector2D operator<<(int16_t s) const {
        return FPVector2D(x << s, y << s);
    }

    // Compound assignment operators
    FPVector2D &operator+=(const FPVector2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    FPVector2D &operator-=(const FPVector2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    FPVector2D &operator=(const FPVector2D &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // Equality and inequality operators
    bool operator==(const FPVector2D &other) const {
        return x == other.x && y == other.y;
    }
    bool operator!=(const FPVector2D &other) const {
        return !(*this == other);
    }

    FPVector2D getDirectionFromAngle(int angle) const {
        int idx = angle % 360; // Ensure the angle wraps around correctly
        return FPVector2D(COS_LUT[idx], SIN_LUT[idx]);
    }
};

#endif /* VECTOR_H_ */
