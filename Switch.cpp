/*
 * Switch.cpp
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"

#define INPUTPINS 0x00002000 // pin 13

void Switch_Init(void){
  IOMUX->SECCFG.PINCM[PB13INDEX] = 0x00040081; // Enables PB13
  GPIOB->DOECLR31_0 |= INPUTPINS; // pin 13
}
// return current state of switches
uint32_t Switch_In(void){
  return (GPIOB->DIN31_0 & INPUTPINS);
}
