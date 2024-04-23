#ifndef STDINT_H_
#define STDINT_H_
#include <stdint.h>
#endif

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#define FP_SHIFT 16
#define PLAYERSPEED 3 << FP_SHIFT
#define PLAYERWIDTH 19
#define PLAYERHEIGHT 19
#define SCREENWIDTH 160
#define SCREENHEIGHT 128
#define TOTAL_SPRITES 24
#define MAX_PROJECTILES 10

#include "Vector.h"
#include "Projectile.h"
#include "../inc/ST7735.h"

class PlayerShip { //  TODO: implement proper movement mechanics and input handling, both here and in TimerG12
public:
    FPVector2D _position, _previousPosition, _velocity, /*_acceleration,*/ _size;
    int32_t _angle;
    const uint16_t** _sprites; // array of sprites for each various angles
    int _spriteIndex; // Based on angle
    int _totalSprites;
    enum BoundaryMode { STOP, WRAP, BOUNCE } _boundaryMode;
    bool _inputLeft, _inputRight;
    Projectile projectiles[MAX_PROJECTILES];

    PlayerShip(int16_t x, int16_t y, int16_t w, int16_t h, int32_t angle, const uint16_t** images, FPVector2D initialVelocity, int totalSprites, BoundaryMode boundaryMode);
    void update();
    void applyForce(const FPVector2D& force);
    void draw(const uint16_t* background);
    void shootProjectile();
    void handleInput();
    void shoot();
    void updateProjectiles();
    void drawProjectiles(const uint16_t* bg);
    void updateProjectiles(const uint16_t* bg);


private:
    void updateSpriteIndex();
};

#endif /* PLAYERSHIP_H_ */
