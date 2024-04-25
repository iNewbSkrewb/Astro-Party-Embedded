#include "ScreenManager.h"
#include "PlayerShip.h"

extern PlayerShip players[2];
extern const uint16_t* bg;

void startScreenUpdate(void){

}

void gameScreenUpdate(uint32_t buttons){
    for (PlayerShip& ship : players) {
        ship.update(buttons);
        ship.updateProjectiles(bg);
    }
}

void winScreenUpdate(void){

}

void drawStartScreen(void){

}
void drawWinScreen(void){

}
void drawGameScreen(void){
    for (PlayerShip& p : players) p.draw(bg);
}
