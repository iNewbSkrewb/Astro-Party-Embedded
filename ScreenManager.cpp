#include "ScreenManager.h"
#include "PlayerShip.h"

extern PlayerShip players[2];
extern const uint16_t* bg;
extern game_state_t game_state;
#include "../inc/SlidePot.h"

extern SlidePot Sensor;

void startScreenUpdate(void){

}

void gameScreenUpdate(uint32_t buttons) {
    for (PlayerShip& ship : players) {
        ship.update(buttons);
        ship.updateProjectiles(bg);
    }

    // Check for collisions between players
    bool collision = players[0].checkCollision(players[1]) || players[1].checkCollision(players[0]);

    if (collision) {
        game_state = WIN; // Change the game state to WIN if a collision is detected
    }
}

void winScreenUpdate(void){
}

void drawStartScreen(void){

}
static int hasWon = 0;
int winner;
void drawWinScreen(void) {
    if (!hasWon){
        hasWon = 1;
    ST7735_FillScreen(ST7735_BLACK);
    winner = (players[0].checkCollision(players[1])) ? 2 : 1;
    }
    ST7735_SetCursor(0, 0);
    if (winner == 1){
        if (Sensor.In() < 2048) ST7735_OutString(" The winner: player 1");
        else                    ST7735_OutString("El ganador: jugador 1");
    }
    else {
        if (Sensor.In() < 2048) ST7735_OutString(" The winner: player 2");
        else                    ST7735_OutString("El ganador: jugador 2");
    }

}
void drawGameScreen(void){
    for (PlayerShip& p : players) p.draw(bg);
}
