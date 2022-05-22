CC=gcc
FLAGS=-Wall

all:game
game: main.c game.h
	$(CC) $(FLAGS) -DDISPLAY -o $@ $^ -lSDL2

clean:
	rm -f game

