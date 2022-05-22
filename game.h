#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

// State represents the state of some step
typedef unsigned char Cell;
struct State{
    Cell** cells; // cells in 2D world
    int width;  // the width of 2D world
    int height;  // the height of 2D world
};

/**
* Read the intial state from the configuration
* @param configFileName configuration filename
* @param initialState inital state
*/
void readConfiguration(char* configFileName, struct State* initialState);

/**
* Run the game until the game needs termination
* @param currentState current state
* @param maximalStep maximal step
*/
void runGame(struct State* currentState, int maximalStep);

/**
* Execute one step
* @param currentState current state
* @param nextState next state
*/
void oneStep(struct State* currentState, struct State* nextState);

/**
* Check if the game should terminate
* @param currentState current state
* @param prevState previous state
* @param curStep current step
* @param maximalStep maximal step
*/
bool shouldTerminate(struct State* currentState, struct State* prevState,
    int curStep, int maximalStep);

/**
* Display current state of the game
* @param currentState current state
*/
void displayCurrentState(struct State* currentState);

/**
* Write the final state into the output file
* @param outputFileName the output filename
* @param finalState final state
*/
void writeState(char* outputFileName, struct State* finalState);

/**
* Free the memeory of the stata
* @param the state
*/
void freeState(struct State* state);
#endif // GAME_H