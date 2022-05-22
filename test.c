#include <stdio.h>
#include <assert.h>
#include "game.h"

extern bool displayMode;

// In this function, I test the reading of inital state.
// The readConfiguration() function should read the inital state correctly.
void testReadInitialState(){
    struct State currentState;
    readConfiguration("inital_state1", &currentState);
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
}

void testWriteFinalState(){

}

void testExecuteOneStep(){

}

void testRunGame(){
    
}


void testCheckIfTheGameOver(){

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