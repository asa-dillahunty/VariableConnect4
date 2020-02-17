/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Asa Dillahunty
 *
 * Date of Last Edit: April 1st, 2019
 *
 * This program, board.c, was desgined to hold and
 * display the played moves and incorporates logic to
 * help game.c determine if rules have been broken.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

struct board
{
    int height;
    int width;
    int plays;
    int maxPlays;
    
    char **field;
};

BOARD *newBoard(int height, int width)
{
    BOARD *board=(BOARD*)malloc(sizeof(BOARD));
    
    board->height=height;
    board->width=width;
    board->plays=0;
    board->maxPlays=height*width;
    board->field=(char**) malloc(height*sizeof(char*));
    
    for (int i=0;i<height;i++)
        board->field[i]=(char*)malloc(width*sizeof(char));
    
    for (int i=0;i<board->height;i++)
        for (int j=0;j<board->width;j++)
            board->field[i][j]=' ';
    
    return board;
}

int getWidth(BOARD* board)
{
    return board->width;
}

int getHeight(BOARD* board)
{
    return board->height;
}

bool boardIsFilled(BOARD* board)
{
    return board->plays==board->maxPlays;
}

char setPosition(BOARD* board, int y, int x, char care)
{
    char temp=board->field[y][x];
    board->field[y][x]=care;
    if (temp==' ') board->plays++;
    return temp;
}

bool notSet(BOARD* board, int y, int x)
{
    return board->field[y][x]==' ';
}

int maxFreeY(BOARD *board, int x)
{
    int maxY=-1;
    for (int i=0;i<board->height;i++)
        if (notSet(board,i,x)) maxY=i;

    return maxY;
}

int maxFreeX(BOARD *board, int y)
{
    int maxX=-1;
    for (int j=0;j<board->width;j++)
        if (notSet(board,y,j)) maxX=j;

    return maxX;
}

bool withInBounds(BOARD* board, int y, int x)
{
    return x<board->width && x>=0 && y<board->height && y>=0;
}

bool isWinner(BOARD *board, int move)
{
    int h=maxFreeY(board,move)+1;
    char care=board->field[h][move];
    
    int minX=move;
    int maxX=move;
    int minY=h;
    int maxY=h;

    //Checks horizontal
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h,move-i))
        {
            if (board->field[h][move-i]==care) minX=move-i;
            else break;
        }
        else break;
    }
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h,move+i))
        {
            if (board->field[h][move+i]==care) maxX=move+i;
            else break;
        }
        else break;
    }
    if (maxX-minX>2) return true;

    minX=move;
    maxX=move;
    minY=h;
    maxY=h;

    //Checks Vertical
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h-i,move))
        {
            if (board->field[h-i][move]==care) minY=h-i;
            else break;
        }
        else break;
    }
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h+i,move))
        {
            if (board->field[h+i][move]==care) maxY=h+i;
            else break;
        }
        else break;
    }
    if (maxY-minY>2) return true;

    minX=move;
    maxX=move;
    minY=h;
    maxY=h;

    //Checks diagonal (line where y=1x+b)
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h-i,move-i))
        {
            if (board->field[h-i][move-i]==care) minX=move-i;
            else break;
        }
        else break;
    }
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h+i,move+i))
        {
            if (board->field[h+i][move+i]==care) maxX=move+i;
            else break;
        }
        else break;
    }
    if (maxX-minX>2) return true;

    minX=move;
    maxX=move;
    minY=h;
    maxY=h;

    //Checks diagonal (line where y=-1x+b)
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h+i,move-i))
        {
            if (board->field[h+i][move-i]==care) minX=move-i;
            else break;
        }
        else break;
    }
    for (int i=0;i<4;i++)
    {
        if (withInBounds(board,h-i,move+i))
        {
            if (board->field[h-i][move+i]==care) maxX=move+i;
            else break;
        }
        else break;
    }
    if (maxX-minX>2) return true;

    return false;
}










int myLog10(int x)
{
    int i;
    for (i=0;x!=0;i++) x=x/10;
    return i-1;
}

int myPow10(int x)
{
    int pow=1;
    for (int i=0;i<x;i++) pow=pow*10;
    return pow; 
}

void printBoard(BOARD* board)
{
    int wid = 2*(board->width+1);
    
    for (int i=0;i<board->height;i++)
    {
        for (int j=0;j<wid-1;j++) printf("-");
        printf("\n|");
        
        for (int j=0;j<board->width;j++) printf("%c|",board->field[i][j]);
        printf("\n");
    }
    
    for (int j=0;j<wid-1;j++) printf("-");
    printf("\n");

    for (int i=myLog10(board->width);i>=0;i--)
    {
        for (int j=0;j<board->width;j++) printf(" %d",j/myPow10(i)%10);
        printf("\n");
    }
    printf("\n");
}

/**
 * This uses more memory than the board, so this can cause the game to crash!
 */
char *toString(BOARD* board)
{
    int wid = 2*(board->width+1);
    int hei = 2*board->height+1;
    
    printf("wid: %d\nhei: %d\n",wid,hei);
    
    char *boardAsString=(char*)malloc(hei*wid*sizeof(char));
    
    for (int i=0;i<board->height;i++)
    {
        for (int j=0;j<wid-1;j++)
        {
            boardAsString[2*i*wid+j]='-';
            printf("-");
        }
        boardAsString[2*i*wid+wid-1]='\n';
        printf("\n|");
        
        for (int j=0;j<board->width;j++)
        {
            //not done
            //Think am close
            if (board->field[i][j]!='\0') boardAsString[2*(i+1)*wid+2*j]=board->field[i][j];
            else boardAsString[2*(i+1)*wid+2*j]=' ';
            
            boardAsString[2*(i+1)*wid+2*(j+1)]='|';
            
            printf(" |");
        }
        boardAsString[2*(i+1)*wid+wid-1]='\n';
        printf("\n");
    }
    
    
    printf("****************************\n");
    
    return boardAsString;
}

void freeBoard(BOARD *board)
{    
    for (int i=0;i<board->height;i++)
        free(board->field[i]);

    free(board->field);
}
