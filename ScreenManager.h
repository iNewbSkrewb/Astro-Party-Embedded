
#ifndef SCREENMANAGER_H_
#define SCREENMANAGER_H_

enum game_state_t {START, GAME, WIN};

void drawStartScreen(void);
void drawWinScreen(void);
void drawGameScreen(void);

void startScreenUpdate(void);
void gameScreenUpdate(void);
void winScreenUpdate(void);

#endif /* SCREENMANAGER_H_ */
