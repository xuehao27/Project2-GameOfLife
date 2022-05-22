#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

int main(int argc, char* argv[]){
    if(argc != 0){
        printf("Usage: %s <pathToConfig> <pathToOutFile>")
        exit(1);
    }
    return 0;
}