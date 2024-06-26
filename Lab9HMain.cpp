#ifndef STDINT_H_
#define STDINT_H_
#include <stdint.h>
#endif

#include <stdio.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
//#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
#include "PlayerShip.h"
#include "SmallFont.h"
#include "Switch.h"
#include "LED.h"
#include "Sound.h"
#include "../images/images.h"
#include "ScreenManager.h"
extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);

void Sound_Init(uint32_t period, uint32_t priority);
void Sound_Start(uint32_t period);
void Sound_Stop(void);


/**
 * @brief This sets the bus speed of the microcontroller, which affects the microcontroller operation frequency
 *
 */
void PLL_Init(void)
{
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0); // run this line for 80MHz
}


SlidePot Sensor(2450, -440); // copy calibration from Lab 7

// Define initial velocities for ships
const FPVector2D initialVelocityShip1(1 << FP_SHIFT, 0);
const FPVector2D initialVelocityShip2(1 << FP_SHIFT, 0);

// Global array of PlayerShip objects
// Correctly initialize the players with all required arguments
PlayerShip players[2] = {
    PlayerShip(40, 60, PLAYERWIDTH, PLAYERHEIGHT, 0, ship1, initialVelocityShip1, TOTAL_SPRITES, PlayerShip::BoundaryMode::STOP, 1, 16, 19),
    PlayerShip(60, 40, PLAYERWIDTH, PLAYERHEIGHT, 0, ship1, initialVelocityShip2, TOTAL_SPRITES, PlayerShip::BoundaryMode::STOP, 0, 13, 17)
};
const uint16_t* bg = orangebg;

game_state_t game_state = GAME;

volatile int semaphore = 0;

// games  engine runs at 30Hz
void TIMG12_IRQHandler(void)
{
  static uint32_t soundTh = 0;
  uint32_t pos, msg;
  if ((TIMG12->CPU_INT.IIDX) == 1)

    uint32_t adcdata = Sensor.In();
    uint32_t buttons = Switch_In();

    switch (game_state){
    case START: startScreenUpdate(); break;
    case GAME: gameScreenUpdate(buttons); break;
    case WIN: winScreenUpdate();
    }
    // 4) start sounds

    semaphore = 1;

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
  Sound_Init(1,0); // initialize switches
  Switch_Init();
  LED_Init();    // initialize LED
  DAC5_Init();
//  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
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
      switch (game_state){
      case START: drawStartScreen(); break;
      case GAME: drawGameScreen(); break;
      case WIN: drawWinScreen();
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

    //uint8_t TExaS_LaunchPadLogicPB27PB26(void)
    //{
    //  return (0x80 | ((GPIOB->DOUT31_0 >> 26) & 0x03));
    //}
    //uint32_t M = 1;
    //uint32_t Random32(void)
    //{
    //  M = 1664525 * M + 1013904223;
    //  return M;
    //}
    //uint32_t Random(uint32_t n)
    //{
    //  return (Random32() >> 16) % n;
    //}
