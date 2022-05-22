#include "game.h"

bool displayMode = true; // This is used to indicate whether the state is displayed on screen.

#ifndef TEST
int main(int argc, char* argv[]){
    // check the least number of arguments
    if(argc < 3){
        printf("Usage: %s <pathToConfig> <pathToOutFile> [maximalStep]\n", argv[0]);
        exit(1);
    }
    // parse the maximal step
    int maximalStep = INT_MAX;
    if(argc > 3){
        maximalStep = atoi(argv[3]);
    }
    // read inital state from the file
    char* configFileName = argv[1];
    struct State currentState;
    readConfiguration(configFileName, &currentState);

    // run the game
    char* outputFileName = argv[2];
    runGame(&currentState, maximalStep);

    // write the final state into a file
    writeState(outputFileName, &currentState);

    // free the memory
    freeState(&currentState);
    return 0;
}
#endif

/**
* Read the intial state from the configuration
* @param configFileName configuration filename
* @param initialState inital state
*/
void readConfiguration(char* configFileName, struct State* initialState){
    FILE* inFile = fopen(configFileName, "r");
    if(!inFile){
        // canot open the file
        perror("ERROR");
        exit(1);
    }
    // read the width and height of 2D world
    fscanf(inFile, "%d%d%*c", &initialState->width, &initialState->height);
    // allocate the memory for the two-dimension array
    initialState->cells = (Cell**)malloc(initialState->height*sizeof(Cell*));
    for(int i = 0; i < initialState->height; i++){
        initialState->cells[i] = (Cell*)malloc(initialState->width*sizeof(Cell));
    }
    // read the cells
    for(int i = 0; i < initialState->height; i++){
        for(int j = 0; j < initialState->width; j++){
            fscanf(inFile, "%c", &initialState->cells[i][j]);
        }
        fgetc(inFile);
    }
    fclose(inFile);
}

/**
* Run the game until the game needs termination
* @param currentState current state
* @param maximalStep maximal step
*/
void runGame(struct State* currentState, int maximalStep){

}

/**
* Execute one step
* @param currentState current state
* @param nextState next state
*/
void oneStep(struct State* currentState, struct State* nextState){
    
}

/**
* Check if the game should terminate
* @param currentState current state
* @param prevState previous state
* @param maximalStep maximal step
*/
bool shouldTerminate(struct State* currentState, struct State* prevState, int maximalStep){
    return false;
}

/**
* Display current state of the game
* @param currentState current state
*/
void displayCurrentState(struct State* currentState){
    
}

/**
* Write the final state into the output file
* @param outputFileName the output filename
* @param finalState final state
*/
void writeState(char* outputFileName, struct State* finalState){
    FILE* outFile = fopen(outputFileName, "w");
    if(!outFile){
        // cannot open the file
        perror("ERROR");
        exit(1);
    }
    // write the width and height of 2D world
    fprintf(outFile, "%d %d\n", finalState->width, finalState->height);
    // write the cells
    for(int i = 0; i < finalState->height; i++){
        if(i > 0){
            fprintf(outFile, "\n");
        }
        for(int j = 0;j < finalState->width; j++){
            fprintf(outFile, "%c", finalState->cells[i][j]);
        }
    }
    fclose(outFile);
}

/**
* Free the memeory of the stata
* @param the state
*/
void freeState(struct State* state){
    for(int i = 0; i < state->height; i++){
        free(state->cells[i]);
    }
    free(state->cells);
}