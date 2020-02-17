#ifndef __PLAYER_INCLUDED__
#define __PLAYER_INCLUDED__

#include "board.h"
#include <stdbool.h>

typedef struct player PLAYER;

extern PLAYER *newPlayer(char care, bool isAI);
extern int getMove(PLAYER *player, BOARD *board);
extern char getChar(PLAYER *player);
extern void freePlayer(PLAYER *player);

#endif