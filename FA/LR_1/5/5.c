#include <stdio.h>
#include <stdlib.h>
#include "include/flagFunctions.h"
#include "include/createOutputPath.h"


int main(int argc, char *argv[]){
        
    if((argc != 3) && (argc != 4)){
        printf("Usage: %s <flag> <input file> (<output file>)\n", argv[0]);
        return -1;
    }

    
    char * flag = argv[1];
    FILE * inputFile = fopen(argv[2], "r");
        if (inputFile == NULL) {
            printf("Error opening input file");
            return -1;
        }

    if((flag[0] == '-') || (flag[0] == '/')){
        if(flag[1] == 'n'){
            if(argc == 4){

                FILE * outputFile = fopen(argv[3], "w");
                if (outputFile == NULL) {
                    printf("Error opening output file");
                    return -1;
                }

                if (flag[2] == 'd') {
                    flagD(inputFile, outputFile);
                    fclose(inputFile);
                    fclose(outputFile);
                } else if (flag[2] == 'i') {
                    flagI(inputFile, outputFile);
                    fclose(inputFile);
                    fclose(outputFile);
                } else if (flag[2] == 's') {
                    flagS(inputFile, outputFile);
                    fclose(inputFile);
                    fclose(outputFile);
                } else if (flag[2] == 'a') {
                    flagA(inputFile, outputFile);
                    fclose(inputFile);
                    fclose(outputFile);
                } else {
                    printf("Undefinded flag");
                }

            } else{
                printf("Usage: %s <flag> <input file> (<output file>)\n", argv[0]);
            }
        } else if (flag[1] == 'd') {
            char* output_path = create_output_path(argv[2]);
            FILE * outputFile = fopen(output_path, "w");
            flagD(inputFile, outputFile);
            fclose(inputFile);
            fclose(outputFile);
            free(output_path);
        } else if (flag[1] == 'i') {
            char* output_path = create_output_path(argv[2]);
            FILE * outputFile = fopen(output_path, "w");
            flagI(inputFile, outputFile);
            fclose(inputFile);
            fclose(outputFile);
            free(output_path);
        } else if (flag[1] == 's') {
            char* output_path = create_output_path(argv[2]);
            FILE * outputFile = fopen(output_path, "w");
            flagS(inputFile, outputFile);
            fclose(inputFile);
            fclose(outputFile);
            free(output_path);
        } else if (flag[1] == 'a') {
            char* output_path = create_output_path(argv[2]);
            FILE * outputFile = fopen(output_path, "w");
            flagA(inputFile, outputFile);
            fclose(inputFile);
            fclose(outputFile);
            free(output_path);
        } else {
            printf("Undefinded flag");
        }
    } else {
        printf("Usage: %s <flag> <input file> (<output file>)\n", argv[0]);
    }

    return 0;
}
