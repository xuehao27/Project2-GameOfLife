#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "game.h"

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Usage: %s <pathToConfig> <pathToOutFile> [maximalStep]\n", argv[0]);
        exit(1);
    }
    int maximalStep = INT_MAX;
    if(argc > 3){
        maximalStep = atoi(argv[3]);
    }

    return 0;
}
