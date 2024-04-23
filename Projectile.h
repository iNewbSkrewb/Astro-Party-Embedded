#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "Vector.h"
#include "../inc/ST7735.h"

class Projectile {
public:
    FPVector2D position;
    FPVector2D velocity;
    const uint16_t* sprite;  // Pointer to the projectile's sprite
    bool active;             // Is the projectile active?
    FPVector2D previousPosition;  // Store the previous position for efficient redrawing

    Projectile() : position(0, 0), velocity(0, 0), sprite(nullptr), active(false) {}

    // Initialize the projectile
    void init(const FPVector2D& pos, const FPVector2D& vel, const uint16_t* spr) {
        position = pos;
        velocity = vel;
        sprite = spr;
        active = true;
        previousPosition = position;  // Initialize previous position
    }

    // Update the projectile's position
    void update() {
        if (active) {
            previousPosition = position;  // Store current position as previous
            position += velocity;

            // Check for boundaries or collisions
            if (position.x < 0 || position.x > (SCREENWIDTH << FP_SHIFT) ||
                position.y < 0 || position.y > (SCREENHEIGHT << FP_SHIFT)) {
                active = false;  // Deactivate if out of bounds
            }
        }
    }

    // Draw the projectile
    void draw(const uint16_t* background) {
        if (active) {
            // Draw the sprite
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    int x = (position.x >> FP_SHIFT) + j;
                    int y = (position.y >> FP_SHIFT) + i;
                    ST7735_DrawPixel(x, y, sprite[i * 2 + j]);
                }
            }
        }
    }

    // Clear the area where the projectile was
    void clear(const uint16_t* background) {
        if (previousPosition != position) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    int x = (previousPosition.x >> FP_SHIFT) + j;
                    int y = (previousPosition.y >> FP_SHIFT) + i;
                    uint16_t bg_color = background[(SCREENHEIGHT - y - 1) * SCREENWIDTH + x]; // Adjust if the coordinate system is inverted
                    ST7735_DrawPixel(x, y, bg_color);
                }
            }
        }
    }
};

#endif // PROJECTILE_H_
