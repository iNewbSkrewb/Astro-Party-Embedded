
#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

#include <stdint.h>

enum game_state_t {START, GAME, WIN};

void drawStartScreen(void);
void drawWinScreen(void);
void drawGameScreen(void);

void startScreenUpdate(void);
void gameScreenUpdate(uint32_t buttons);
void winScreenUpdate(void);

#endif /* SCREENMANAGER_H_ */
