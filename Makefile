CC=gcc
FLAGS=-Wall -Werror

all:game
game: main.c game.h
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -f game

test:
	$(CC) $(FLAGS) -o test test.c main.c main.h
