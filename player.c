/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Asa Dillahunty
 *
 * Date of Last Edit: April 1st, 2019
 *
 * This program, player.c, was designed to store data
 * on a current player, and handle the decision making
 * process of getting moves. This is especially important
 * when dealing with computer players.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "board.h"
#include "player.h"
#include "interface.h"

int someFunct(PLAYER *player, BOARD *board);
int randMove(PLAYER *player, BOARD *board);

/* *
 * Each player has their own character shown when played
 * and either is a computer player or a real person
 */
struct player
{
    bool isAI;
    char care;
};

/* *
 * This is a construtor to handle the allocation of
 * data when making a player pointer
 *
 * @param care: care is the player's unique character
 * @param isAI: isAI determines if the player is a
 *              computer player or not
 * @returns PLAYER*: returns a player with set values.
 */
PLAYER* newPlayer(char care, bool isAI)
{
    PLAYER* player = (PLAYER*) malloc(sizeof(PLAYER));
    player->care=care;
    player->isAI=isAI;

    return player;
}

char getChar(PLAYER* player)
{
    return player->care;
}

int getMove(PLAYER *player, BOARD *board)
{
    if (player->isAI) return randMove(player, board);

    printBoard(board);
    printf("You are: %c\nWhere would you like to play?\n", player->care);
    return getNum("A number I can fit on the board please\n",0,getWidth(board)-1);
}

int someFunct(PLAYER *player, BOARD *board)
{
    int width=getWidth(board);
    if (width==getChar(player)) printf("Width equals my char!\n");

    for (int i=0;i<width;i++)
    {
        if (notSet(board,0,i)) return i;
    }
    return 0;
}

int randMove(PLAYER *player, BOARD *board)
{
    int width=getWidth(board);
    if (width==getChar(player)) printf("Width equals my char!\n");

    int i;
    for (;;)
    {
        i=rand()%width;
        if (notSet(board,0,i)) return i;
    }
    return 0;
}

void freePlayer(PLAYER *player)
{
    free(player);
}
