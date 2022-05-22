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
    if(!configFileName || !initialState) return;
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
    if(!currentState) return;
    // allocate a state
    struct State nextState;
    nextState.width = currentState->width;
    nextState.height = currentState->height;
    nextState.cells = (Cell**)malloc(nextState.height*sizeof(Cell*));
    for(int i = 0; i < nextState.height; i++){
        nextState.cells[i] = (Cell*)malloc(nextState.width*sizeof(Cell));
    }
    
}

/**
* Execute one step
* @param currentState current state
* @param nextState next state
*/
void oneStep(struct State* currentState, struct State* nextState){
    if(!currentState || !nextState) return;

    for(int iRow = 0; iRow < currentState->height; iRow++){
        for(int iCol = 0; iCol < currentState->width; iCol++){
            // compute the number of alive cells
            int num = 0;
            for(int i = -1; i <= 1; i++){
                for(int j = -1; j <= 1; j++){
                    if(i == 0 && j == 0){
                        continue;
                    }
                    int mRow = iRow + i;
                    int mCol = iCol + j;
                    if(mRow < 0 || mCol < 0 || mRow >= currentState->height ||
                        mCol >= currentState->width){
                            // the location is invalid
                            continue;
                        }
                    if(currentState->cells[mRow][mCol] == '1'){
                        num++;
                    }
                }
            }
            // compute the status of the cell in next step
            if(currentState->cells[iRow][iCol] == '0'){
                if(num == 3){
                    nextState->cells[iRow][iCol] = '1';
                }else{
                    nextState->cells[iRow][iCol] = '0';
                }
            }else{
                if(num == 2 || num == 3){
                    nextState->cells[iRow][iCol] = '1';
                }else{
                    nextState->cells[iRow][iCol] = '0';
                }
            }
        }
    }
}

/**
* Check if the game should terminate
* @param currentState current state
* @param prevState previous state
* @param curStep current step
* @param maximalStep maximal step
*/
bool shouldTerminate(struct State* currentState, struct State* prevState, 
    int curStep, int maximalStep){
    if(!currentState || !prevState) return true;
    if(curStep > maximalStep) return true;
    // check if the state has changed
    for(int iRow = 0; iRow < currentState->height; iRow++){
        for(int iCol = 0; iCol < currentState->width; iCol++){
            if(currentState->cells[iRow][iCol] != prevState->cells[iRow][iCol]){
                return false;
            }
        }
    }
    return true;
}

/**
* Display current state of the game
* @param currentState current state
*/
void displayCurrentState(struct State* currentState){
    if(!currentState) return;

}

/**
* Write the final state into the output file
* @param outputFileName the output filename
* @param finalState final state
*/
void writeState(char* outputFileName, struct State* finalState){
    if(!outputFileName || !finalState) return;
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