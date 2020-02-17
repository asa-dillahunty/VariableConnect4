OBJS = interface.o game.o board.o player.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : launch

launch: $(OBJS)
	gcc $(LOPTS) $(OBJS) -o launch

interface.o: interface.c interface.h game.h player.h
	gcc $(OOPTS) interface.c

game.o: game.c game.h interface.h board.h player.h
	gcc $(OOPTS) game.c

board.o: board.c board.h
	gcc $(OOPTS) board.c

player.o: player.c player.h game.h board.h interface.h
	gcc $(OOPTS) player.c

test: launch
	./launch

clean:
	rm -f $(OBJS) launch

