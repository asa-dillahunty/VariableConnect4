#ifndef __BOARD_INCLUDED__
#define __BOARD_INCLUDED__

typedef struct board BOARD;

extern BOARD *newBoard(int height, int width);
extern char *toString(BOARD* board);
extern void printBoard(BOARD* board);
extern char setPosition(BOARD* board, int x, int y, char care);
extern bool notSet(BOARD* board, int y, int x);
extern int maxFreeY(BOARD *board, int x);
extern int maxFreeX(BOARD *board, int y);
extern void freeBoard(BOARD *board);
extern int getWidth(BOARD* board);
extern int getHeight(BOARD* board);
extern bool boardIsFilled(BOARD* board);
extern bool isWinner(BOARD *board, int move);

#endif
