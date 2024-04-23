/*
 * Vector.h
 *
 *  Created on: Apr 21, 2024
 *      Author: samie
 */

#ifndef VECTOR_H_
#define VECTOR_H_

// Fixed point 2D vector class
class FPVector2D {
public:
    int32_t x, y;

    FPVector2D(void){
            x = y = 0;
        }

    FPVector2D(int32_t xx, int32_t yy){
        x = xx; y = yy;
    }
    FPVector2D operator+(const FPVector2D& other) const {
        return FPVector2D(x+other.x, y+other.y);
    }

    inline FPVector2D& operator+=(const FPVector2D& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    inline FPVector2D& operator-=(const FPVector2D& other) {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

    FPVector2D& operator=(const FPVector2D& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
    }

    FPVector2D operator-(const FPVector2D& other) const {
        return FPVector2D(x-other.x, y-other.y);
    }
    FPVector2D operator*(const int16_t s) const {
        return FPVector2D(x*s, y*s);
    }
    FPVector2D operator/(const int16_t s) const {
            return FPVector2D(x/s, y/s);
    }
    FPVector2D operator>>(const int16_t s) const {
            return FPVector2D(x>>s, y>>s);
    }
};


#endif /* VECTOR_H_ */
