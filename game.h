#ifndef __GAME_INCLUDED__
#define __GAME_INCLUDED__

#include "player.h"

typedef struct game GAME;

extern GAME *newGame(int humanPlayers, int AIPlayers);
extern int startGame(GAME* game, int height, int width, PLAYER* player1, PLAYER* player2);
extern bool playMove(GAME *game, int x, char care);
extern bool canPlay(GAME *game, int x);
extern void freeGame(GAME *game);

#endif
