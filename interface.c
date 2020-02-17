/* * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @Author: Asa Dillahunty
 * 
 * Date of Last Edit: April 1st, 2019
 *
 * The Purpose of this Program is to play connect 4,
 * and was orignally designed to implement path finding
 * algorithms, but do to the nature of connect 4, that
 * would be inefficient and was not technically used.
 *
 * This program, interface.c, is to serve as the
 * interface between the players and the game. It is
 * used to get responses and to start the actual game.
 *
 * It also holds the main function used to actually
 * execute things.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "interface.h"
#include "game.h"
#include "player.h"

void printFile(char* filename);
void printMenu();
void playMatch(PLAYER *player1, PLAYER *player2);

//largest string that can be read from a file
const int MAX_LENGTH=500;

/**
 * Main method. Used only to execute code
 * @return: returns 0 if executed properly
 */
int main(void)
{
    startInterface();
    return 0;
}

/**
 * This function handles the main menu
 */
void startInterface()
{
	printFile("title.txt");

	printf("\n\nHello! Welcome to Asa's Rendition of Connect Four!\nThe Weird chunk of text above is actual a title! Make the terminal window larger to view it.\n");
	
	bool playing=true;
	int ans=0;
	PLAYER* player1;
	PLAYER* player2;

	printf("Would you like to play? [y/n]\n");
	playing=yesNo("Answer \"yes\" or \"no\" please\n");
		
	while(playing)
	{
		printMenu();
		ans=getNum("A number on the menu please.\n",1,5);

		switch(ans)
		{
			case 0:
				printf("Settings are restricted\n");
				break;
			case 1:
				printFile("readme.md");
				break;
			case 2:
				player1 = newPlayer('X',false);
				player2 = newPlayer('O',true);
				playMatch(player1,player2);
				freePlayer(player1);
				freePlayer(player2);
				break;
			case 3:
				player1 = newPlayer('X',false);
				player2 = newPlayer('O',false);
				playMatch(player1,player2);
				freePlayer(player1);
				freePlayer(player2);
				break;
			case 4:
				printFile("title.txt");
				break;
			case 5:
				playing=false;
				break;
            //Default should never be activated, but it is good practice to include one
			default:
				printf("Not sure what happened. Try to select again.\n");
		}
	}
}

/**
 * This function simply prints a file exactly as it exists
 *
 * @param filename: The name of the file to be printed
 */
void printFile(char* filename)
{
	char line[MAX_LENGTH];
	FILE *in=fopen(filename,"r");
	
	while (fgets(line,MAX_LENGTH,in)) printf("%s",line);
    
	fclose(in);
}

/**
 * Gets a numeric decimal response from the user
 * It is currently set to recieve from standard input,
 * but could easily be edited using fscanf to recieve
 * input from any file. Though that wasn't necessary
 *
 * @param response: The response to be printed when given illegal input
 * @param min: The minimun number allowed
 * @param max: The maximum number allowed
 * !!! If max < min there is no maximum, just a minimum !!!
 * @return int: returns the first decimal number entered by the user.
 */
int getNum(char* response, int min, int max)
{
	int ans=min-1;
	int result=0;
	char trash=' ';
	
	if (min<max)
	{
		while (ans<min || ans>max || result==0)//implementation where there is a max
		{
			result = scanf("%d",&ans);

            //This is my attempt of eliminating String or char responses
			while (result==0 && trash != '\n')
			{
				scanf("%c",&trash);
				result = scanf("%d",&ans); // if fails to read an int, result = 0
			}
            //The response is only printed when a wrong number is entered
            //A character or String input will be met with no error statements
			if (ans<min || ans>max || result==0) printf("%s",response);
		}
		return ans;
	}
    
	while (ans<min || result==0) //implementation without a max
	{
		result = scanf("%d",&ans);

        //This is my attempt of eliminating String or char responses
		while (result==0 && trash != '\n')
		{
			scanf("%c",&trash);
			result = scanf("%d",&ans); //if fails to read an int, result = 0
		}
        //The response is only printed when a wrong number is entered
        //A character or String input will be met with no error statements
		if (ans<min || result==0) printf("%s",response);
	}
	return ans;
}

/**
 * Gets a yes or no response from the input (currently stdin)
 *
 * @param response: the response printed when given illegal input
 * @return bool: returns true if yes or its synonym is input and false if no or its synonym is input
 */
bool yesNo(char* response)
{
	char ans[MAX_LENGTH];
	ans[0]='f';
	while(true)
	{
		fgets(ans,MAX_LENGTH,stdin);
		/*
            fgets grabs the '\n' character at the end of the response
            so the action below replaces the last character with a
            null character, '\0', to signal the end of the string
		 */
		ans[strlen(ans)-1]='\0';

		if (!strcmp(ans,"y") || !strcmp(ans,"sure") || !strcmp(ans,"yeah") || !strcmp(ans,"yes")) return true;
		if (!strcmp(ans,"n") || !strcmp(ans,"no") || !strcmp(ans,"nope") || !strcmp(ans,"nah")) return false;
		printf("%s",response);
	}
}

void printMenu()
{
	printf("\n\nEnter a numeric value coresponding to the option of your choice.\n");
	printf("[1] Help\n");
	printf("[2] Play vs Computer\n");
	printf("[3] Two Player\n");
	printf("[4] Print Title\n");
	printf("[5] Quit\n");
}

void playMatch(PLAYER *player1, PLAYER *player2)
{
    int p1score=0;
    int p2score=0;
    
    char p1care='X';
    char p2care='O';
    
    int height;
    int width;
    
    int winner;
    bool playing=1;
    
    while (playing)
    {
        printf("What would you like the board height to be?\n");
        height=getNum("A number? Please?\n",4,-1);
        
        printf("What would you like the board width to be?\n");
        width=getNum("A number? Please?\n",4,-1);
        
        printf("Time for game %d! Good luck!\n",(1+p1score+p2score));
        GAME* game = newGame(1,1);
        
        winner = startGame(game, height, width, player1, player2);
		freeGame(game);
		switch (winner)
		{
			case 0:
				printf("Looks like a tie game!\n");
				break;
			case 1:
				printf("Looks like Player 1 won! Nice Job!\n");
				p1score++;
				break;
			case 2:
				printf("Looks like Player 2 won! Nice Job!\n");
				p2score++;
				break;
			default:
				printf("Something went horribly wrong. Please try again\n");
		}
		
		printf("The current score is %d for Player 1 and %d for Player 2. Would you like to keep playing?\n", p1score, p2score);
        
		playing=yesNo("Please enter yes or no\n");
    }

	printf("Thanks for playing! %c%c\n",p1care,p2care);
}
