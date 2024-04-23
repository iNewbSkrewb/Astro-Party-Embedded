/*
 * Switch.cpp
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"

#define INPUTPINS 0x123000 //(1 << 12) & (1 << 13) & (1 << 17) & (1 << 20);

// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    IOMUX->SECCFG.PINCM[PB12INDEX] = 0x00040081; // Enables PB12
    GPIOB->DOECLR31_0 = INPUTPINS; // pin 12
}
// return current state of switches
uint32_t Switch_In(void){
    // write this
  return GPIOB->DIN31_0 & ~(INPUTPINS);
}
