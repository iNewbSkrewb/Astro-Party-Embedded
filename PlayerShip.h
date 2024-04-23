/*
 * PlayerShip.h
 *
 *  Created on: Apr 22, 2024
 *      Author: samienr
 */

#ifndef PLAYERSHIP_H_
#define PLAYERSHIP_H_

#define PLAYERSPEED 20
#define PLAYERWIDTH 22
#define PLAYERHEIGHT 22
#define SCREENWIDTH 160
#define SCREENHEIGHT 128
#define FP_SHIFT 16

#include <stdint.h>
#include "Vector.h"
#include "../inc/ST7735.h"

class PlayerShip { //  TODO: implement proper movement mechanics and input handling, both here and in TimerG12
public:
    FPVector2D pos, prevPos, vel, accel, size;
    char angle; // TODO: make LUT
    const uint16_t** sprites; // array of sprites for each various angles
    uint8_t spriteInd; // based on angle

    PlayerShip(int16_t x, int16_t y, int16_t w, int16_t h, char a, const uint16_t** images);
    void update(void);
    void applyForce(FPVector2D f);
    void draw(uint16_t* bg);
    void ShootProjectile(void);
};


#endif /* PLAYERSHIP_H_ */
