# Connect Four, but Bigger
Author: Asa Dillahunty

Release Date: 3/31/19

## HOW TO RUN 

Type "make test" into the terminal
while in the folder. This assumes
you have make installed
otherwise, type in 

```bash
gcc -Wall -Wextra -g -c interface.c
gcc -Wall -Wextra -g -c game.c
gcc -Wall -Wextra -g -c board.c
gcc -Wall -Wextra -g -c player.c
gcc -Wall -Wextra -g interface.o game.o board.o player.o -o launch
./launch
```

## How to Play

It's standard connect 4, but the board can have crazy dimensions.
Enter the column you want your mark to fall, and it will fall to the lowest unoccupied spot.
The objective is to get four in a row.
This can be achieved horizontally, vertically, or diagonally.

The computer player is completely random and not fun to play against at the moment.

## Rules


1. Neither height nor width of the board size can be less than four.
2. Connecting four in a row (diagonally, horizontally, or vertically) wins you the game!
