CC=gcc
FLAGS=-Wall

all:game
game: main.c game.h
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -f game

