#include "PlayerShip.h"

PlayerShip::PlayerShip(int16_t x, int16_t y, int16_t w, int16_t h, char a, const uint16_t** images) {
    pos = FPVector2D(x << FP_SHIFT, y << FP_SHIFT);
    vel = FPVector2D(1 << FP_SHIFT,0); // TODO: set to default velocity
    accel = FPVector2D(0,0);
    size = FPVector2D(w << FP_SHIFT, h << FP_SHIFT);
    angle = a;
    sprites = images;
    spriteInd = 0;
    if (a > 32) {
        spriteInd = (a - 1) / 32; // select the correct angled sprite depending on angle
    }
}

void PlayerShip::update(void){
    vel += accel;
    pos += vel;
    accel.x = 0; accel.y = 0;

    angle++;
    spriteInd = (angle - 1) / 32;

    if (pos.x < 0) pos.x = 0;
    if (pos.x > ((SCREENWIDTH << FP_SHIFT) - size.x) ) pos.x = ((SCREENWIDTH << FP_SHIFT) - size.x);
    if (pos.y < 0) pos.y = 0;
    if (pos.y > ((SCREENHEIGHT << FP_SHIFT) - size.y) ) pos.y = ((SCREENHEIGHT << FP_SHIFT) - size.y);
}

void PlayerShip::applyForce(FPVector2D f){
    accel += f;
}

void PlayerShip::draw(const uint16_t* bg){
    int startX = pos.x >> FP_SHIFT; // Convert back to integer
    int startY = pos.y >> FP_SHIFT;
    int endX = (pos.x + size.x) >> FP_SHIFT;
    int endY = (pos.y + size.y) >> FP_SHIFT; // getting exact coordinates to draw sprite

    for (int y = startY; y < endY && y < SCREENHEIGHT; ++y) { // for each row
        for (int x = startX; x < endX && x < SCREENWIDTH; ++x) { // for each column

            int pixelIndex = ((y - startY) * (size.x >> FP_SHIFT)) + (x - startX);
            uint16_t color = sprites[spriteInd][pixelIndex];
            if (color != 0x0) { // Non-transparent pixel
                ST7735_DrawPixel(x, y, color);
            }
            else {
                // Draw background pixel
                uint16_t bgColor = bg[((SCREENHEIGHT-y) * SCREENWIDTH) + x];
                ST7735_DrawPixel(x, y, bgColor);
            }
        }
    }
}

void PlayerShip::ShootProjectile(void){
    if (Switch_In() & (1<<12)) {
        if(ActiveProjectiles[0].Active == false){
            ActiveProjectiles[0].Active = true;
            // call draw function for projectile
            ActiveProjectiles[0].drawProjectile();
        }
        else if(ActiveProjectiles[1].Active == false){
            ActiveProjectiles[1].Active = true;
            // call draw function for projectile
            ActiveProjectiles[1].drawProjectile();
        }
        else if(ActiveProjectiles[2].Active == false){
            ActiveProjectiles[2].Active = true;
            // call draw function for projectile
            ActiveProjectiles[2].drawProjectile();
        }
    }
}
