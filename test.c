#include <stdio.h>
#include <assert.h>
#include "game.h"

extern bool displayMode;

// In this function, I test the reading of inital state.
// The readConfiguration() function should read the inital state correctly.
void testReadInitialState(){
    struct State currentState;
    readConfiguration("initial_state1", &currentState);
    // check if current state is correct
    unsigned char expectedCells[][6] = {
        "00000", "00100", "10100", "01100","00000"
    };
    assert(currentState.width == 5);
    assert(currentState.height == 5);
    for(int i = 0; i < 5; i++){
        for(int j = 0;j < 5; j++){
            assert(currentState.cells[i][j] == expectedCells[i][j]);
        }
    }
    freeState(&currentState);
}

void testWriteFinalState(){
    struct State currentState;
    readConfiguration("initial_state1", &currentState);
    // write this stat into the file
    writeState("out1.txt", &currentState);
    freeState(&currentState);

    readConfiguration("out1.txt", &currentState);
    // check if current state is correct
    unsigned char expectedCells[][6] = {
        "00000", "00100", "10100", "01100","00000"
    };
    assert(currentState.width == 5);
    assert(currentState.height == 5);
    for(int i = 0; i < 5; i++){
        for(int j = 0;j < 5; j++){
            assert(currentState.cells[i][j] == expectedCells[i][j]);
        }
    }
    freeState(&currentState);
}

void testExecuteOneStep(){
    struct State currentState;
    readConfiguration("initial_state1", &currentState);
    // allocate a state
    struct State nextState;
    nextState.width = currentState.width;
    nextState.height = currentState.height;
    nextState.cells = (Cell**)malloc(nextState.height*sizeof(Cell*));
    for(int i = 0; i < nextState.height; i++){
        nextState.cells[i] = (Cell*)malloc(nextState.width*sizeof(Cell));
    }

    // calcualte next step
    oneStep(&currentState, &nextState);
    // check if the result is correct
    unsigned char expectedCells[][6] = {
        "00000", "01000", "00110", "01100","00000"
    };
    assert(nextState.width == 5);
    assert(nextState.height == 5);
    for(int i = 0; i < 5; i++){
        for(int j = 0;j < 5; j++){
            assert(nextState.cells[i][j] == expectedCells[i][j]);
        }
    }

    freeState(&currentState);
    freeState(&nextState);
}

void testRunGame(){
    
}


void testCheckIfTheGameOver(){
    struct State currentState;
    readConfiguration("initial_state1", &currentState);

    assert(shouldTerminate(&currentState, &currentState, 1, 10));
    // allocate a state
    struct State nextState;
    nextState.width = currentState.width;
    nextState.height = currentState.height;
    nextState.cells = (Cell**)malloc(nextState.height*sizeof(Cell*));
    for(int i = 0; i < nextState.height; i++){
        nextState.cells[i] = (Cell*)malloc(nextState.width*sizeof(Cell));
    }
    // calcualte next step
    oneStep(&currentState, &nextState);
    assert(!shouldTerminate(&currentState, &nextState, 2, 8));
}

int main(){
    // test suite
    testReadInitialState();
    testWriteFinalState();
    testExecuteOneStep();
    testRunGame();
    testCheckIfTheGameOver();
    return 0;
}