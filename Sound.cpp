// Sound.cpp
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// Jonathan Valvano
// 11/15/2021 
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/DAC5.h"
#include "../inc/Timer.h"

uint32_t static index;
uint8_t soundChoice;

void Sound_Init(uint32_t period, uint32_t priority){
    SysTick->CTRL  = 0x00;      // disable during initialization
    SysTick->LOAD  = period-1;  // set reload register
    //The ARM Cortex-M0+ only implements the most significant 2 bits of each 8-bit priority field (giving the 4 priority levels).
    SCB->SHP[1]    = (SCB->SHP[1]&(~0xC0000000))|priority<<30;    // set priority (bits 31,30)
    SysTick->VAL   = 0;         // clear count, cause reload
    SysTick->CTRL  = 0x07;      // Enable SysTick IRQ and SysTick Timer
}
void Sound_Stop(void){
  // either set LOAD to 0 or clear bit 1 in CTRL
  // write this
    SysTick->LOAD = 0;
}


void Sound_Start(uint32_t period){
  // write this
  // set reload value
  // write any value to VAL, cause reload
    SysTick->LOAD  = period-1;  // set reload register
    SysTick->VAL = 1;
}

extern "C" void SysTick_Handler(void);

// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
    // Assuming 'index' is already declared globally
    if(soundChoice == 0){
        index++;
            DAC5_Out(shoot[index] >> 3);
            if(index >= 4080){
                index = 0;
                Sound_Stop();
            }
    }
    if(soundChoice == 1){
        index++;
            DAC5_Out(explosion[index] >> 3);
            if(index >= 2000){
                index = 0;
                Sound_Stop();
            }
    }
}

