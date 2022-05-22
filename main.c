#include "game.h"

SDL_Renderer* renderer;
SDL_Window* window;
#define SIZE 80


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
    
    // run the game until the game needs termination
    // initiate SDL
#ifdef DISPLAY
    window = SDL_CreateWindow("SDL2:GameOfLife", 
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    SIZE*currentState->width+3*(currentState->width+1),
    SIZE*currentState->height+3*(currentState->height+1),
    SDL_WINDOW_SHOWN);

    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
#endif

    int curStep = 1;
    while(true){
        // execute one step
        oneStep(currentState, &nextState);
#ifdef DISPLAY
        // display this state
        displayCurrentState(currentState);
#endif
        sleep(1);
        if(shouldTerminate(currentState, &nextState, curStep, maximalStep)){
            // the gmae terminates
            break;
        }
        // copy the state
        for(int iRow = 0; iRow < currentState->height; iRow++){
            for(int iCol = 0; iCol < currentState->width; iCol++){
                currentState->cells[iRow][iCol] = nextState.cells[iRow][iCol];
            }
        }
        curStep++;
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
    // draw the cells
    for(int iRow = 0; iRow < currentState->height; iRow++){
        for(int iCol = 0; iCol < currentState->width; iCol++){
            // define the cells
            SDL_Rect rect;
            rect.x = (SIZE+3)*iCol+3;
            rect.y = (SIZE+3)*iRow+3;
            rect.w = SIZE;
            rect.h = SIZE;
            if(currentState->cells[iRow][iCol] == '1'){
                // Black square represents alive cell.
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }else{
                // White square represents dead cell.
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    // draw the seperators
    SDL_SetRenderDrawColor(renderer, 140, 140, 140, 255);
    for(int iCol = 0; iCol < currentState->width; iCol++){
        // define vertical lines
        SDL_Rect mRect;
        mRect.x = (SIZE+3)*iCol;
        mRect.y = 0;
        mRect.w = 3;
        mRect.h = SIZE*currentState->height+3*(currentState->width+1);
        
        SDL_RenderFillRect(renderer, &mRect);
    }
    for(int iRow = 0; iRow < currentState->height; iRow++){
        // define horizontal lines
        SDL_Rect mRect;
        mRect.x = 0;
        mRect.y = (SIZE+3)*iRow;
        mRect.w = SIZE*currentState->width+3*(currentState->width+1);
        mRect.h = 3;
        SDL_RenderFillRect(renderer, &mRect);
    }
    SDL_RenderPresent(renderer);
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