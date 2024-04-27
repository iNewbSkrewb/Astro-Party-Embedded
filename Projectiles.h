#ifndef PROJECTILES_H_
#define PROJECTILES_H_
#include "Vector.h"

#define PROJWIDTH 12
#define PROJHEIGHT 12
#define SCREENWIDTH 160
#define SCREENHEIGHT 128
#define FP_SHIFT 16

class Projectiles{

public:

    bool Active = true;
    FPVector2D posp;
    FPVector2D size;
    FPVector2D vel;
    char angle;



    Projectiles(int16_t x, int16_t y, int16_t w, int16_t h, char a) { // constructor
            posp = FPVector2D(x << FP_SHIFT, y << FP_SHIFT);
            vel = FPVector2D(1 << FP_SHIFT,0); // TODO: set to default velocity
            size = FPVector2D(w << FP_SHIFT, h << FP_SHIFT);
            angle = a;
            Active = false;
    }



    void DestroyOutOfBounds(void){
                if (posp.x < 0) Active = false;
                if (posp.x > ((SCREENWIDTH << FP_SHIFT) - size.x) ) Active = false;
                if (posp.y < 0) Active = false;
                if (posp.y > ((SCREENHEIGHT << FP_SHIFT) - size.y) ) Active = false;
            }


    void ProjectilesUpdate(int16_t newx, int16_t newy, int16_t neww, int16_t newh, char newa){
        this->posp.x = newx;
        this->posp.y = newy;
        this->size.x = neww;
        this->size.y = newh;
        this->angle = newa;
    }

    void drawProjectile(void){

            int startX = posp.x >> FP_SHIFT; // Convert back to integer
            int startY = posp.y >> FP_SHIFT;
            int endX = (posp.x + size.x) >> FP_SHIFT;
            int endY = (posp.y + size.y) >> FP_SHIFT;



            // HAVE SAMIEN LOOK AT THIS
            // HAVE SAMIEN LOOK AT THIS
            // HAVE SAMIEN LOOK AT THIS


            for (int y = startY; y < endY && y < SCREENHEIGHT; ++y) {
                for (int x = startX; x < endX && x < SCREENWIDTH; ++x) {
                    int pixelIndex = ((y - startY) * (size.x >> FP_SHIFT)) + (x - startX);
                    //uint16_t color = sprites[spriteInd][pixelIndex];

                    //if (color != 0x0) { // Non-transparent pixel
                        //ST7735_DrawPixel(x, y, color);
                    }
                }
            }
        };

 // end of Projectile class




#endif /* PROJECTILES_H_ */
