#ifndef STDINT_H_
#define STDINT_H_
#include <stdint.h>
#endif

#include <stdio.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
#include "PlayerShip.h"
#include "SmallFont.h"
#include "Switch.h"
#include "LED.h"
#include "Sound.h"
#include "images.h"
extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);

/**
 * @brief This sets the bus speed of the microcontroller, which affects the microcontroller operation frequency
 *
 */
void PLL_Init(void)
{
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0); // run this line for 80MHz
}

uint32_t M = 1;
uint32_t Random32(void)
{
  M = 1664525 * M + 1013904223;
  return M;
}
uint32_t Random(uint32_t n)
{
  return (Random32() >> 16) % n;
}

SlidePot Sensor(1500, 0); // copy calibration from Lab 7

// Define initial velocities for ships
const FPVector2D initialVelocityShip1(1 << FP_SHIFT, 0);
const FPVector2D initialVelocityShip2(1 << FP_SHIFT, 0);

// Global array of PlayerShip objects
// Correctly initialize the players with all required arguments
PlayerShip players[2] = {
    PlayerShip(40, 60, PLAYERWIDTH, PLAYERHEIGHT, 0, ship1, initialVelocityShip1, TOTAL_SPRITES, PlayerShip::BoundaryMode::STOP),
    PlayerShip(60, 40, PLAYERWIDTH, PLAYERHEIGHT, 0, ship1, initialVelocityShip2, TOTAL_SPRITES, PlayerShip::BoundaryMode::STOP)
};
const uint16_t* bg = orangebg;

volatile int semaphore = 0;
// games  engine runs at 30Hz
void TIMG12_IRQHandler(void)
{
  uint32_t pos, msg;
  if ((TIMG12->CPU_INT.IIDX) == 1)
  {                             // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
                                // game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    if (Switch_In() & (1<<13)){
      players[1].handleInput();
      players[1].shoot();
    }
    for (PlayerShip& ship : players) {ship.update(); ship.updateProjectiles(bg);}
    semaphore = 1;
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}

uint8_t TExaS_LaunchPadLogicPB27PB26(void)
{
  return (0x80 | ((GPIOB->DOUT31_0 >> 26) & 0x03));
}


int main(void)
{ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_InitR(INITR_BLACKTAB);
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetRotation(1);
  ST7735_DrawBitmap(0, 128, bg, 160, 128);
  Sensor.Init(); // PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
  TimerG12_IntArm(80000000 / 30, 2);
  __enable_irq();

  // The while loop runs the game engine
  // 1) sample slide pot
  // 2) read input switches
  // 3) move sprites
  // 4) start sounds
  // 5) set semaphore
  // 6) draw to LCD
  
  while(1){
    // wait for semaphore
      while (!semaphore){};
       // clear semaphore
      semaphore = 0;
       // update ST7735R
      for (PlayerShip& p : players){
          p.draw(bg);
      }
    // check for end game or level switch
  }
}


// Tests

  // const uint16_t* currentFrame = ship1[0];  // Pointer to the first frame

  //   int startX = 40;
  //   int startY = 60;

  //   // Drawing the sprite pixel by pixel
  //   for (int i = 0; i < PLAYERHEIGHT; i++) {
  //       for (int j = 0; j < PLAYERWIDTH; j++) {
  //           int index = i * PLAYERWIDTH + j;  // Calculate index in the frame array
  //           uint16_t color = currentFrame[index];  // Get the pixel color from the frame array
  //           ST7735_DrawPixel(startX + j, startY + i, color);  // Draw the pixel at the correct location
  //       }
  //   }
