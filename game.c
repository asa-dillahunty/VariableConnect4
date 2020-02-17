/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Asa Dillahunty
 *
 * Date of Last Edit: April 1st, 2019
 *
 * This program, game.c, is desgined to run the game and
 * handle transactions between the board and the players.
 * The game handles the rules and was originally designed
 * to determine who wins, but that showed more difficult
 * so it is instead handled by the board.
 */

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "game.h"
#include "board.h"
#include "player.h"

struct game
{
    int humanPlayers;
    int AIPlayers;
    
    BOARD *board;
};

GAME *newGame(int humanPlayers, int AIPlayers)
{
    GAME *game=(GAME*)malloc(sizeof(GAME));
    
    game->AIPlayers=AIPlayers;
    game->humanPlayers=humanPlayers;
    game->board=NULL;
    
    return game;
}

int startGame(GAME* game, int height, int width, PLAYER* player1, PLAYER* player2)
{
    game->board=newBoard(height,width);
    int move;

    while (!boardIsFilled(game->board))
    {
        move=getMove(player1, game->board);
        while (!canPlay(game,move))
            move=getMove(player1,game->board);

        playMove(game,move,getChar(player1));
        
        if (isWinner(game->board,move)) return 1;//is winner

        move=getMove(player2, game->board);
        while (!canPlay(game,move))
            move=getMove(player2,game->board);
            
        playMove(game,move,getChar(player2));
        
        if (isWinner(game->board,move)) return 2;//is winner
    }
    //printf("%s",toString(game->board));
    return 0;
}

bool playMove(GAME *game, int x, char care)
{
    if (canPlay(game,x))
    {
        setPosition(game->board, maxFreeY(game->board,x), x, care);
        return true;
    }
    else return false;
}

bool canPlay(GAME *game, int x)
{
    return notSet(game->board,0,x);
}

void freeGame(GAME *game)
{
    if (game->board) freeBoard(game->board);
    free(game);
}
