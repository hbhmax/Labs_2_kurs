#include <stdio.h>
#include <stdlib.h>
#include "include/switchSystem.h"


int main(int argc, char *argv[]){
        
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return -1;
    }

    FILE * inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            printf("Error opening input file");
            return -1;
        }

    FILE * outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Error opening output file");
        return -1;
    }

    switchSystem(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
