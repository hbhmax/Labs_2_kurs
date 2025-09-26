#include "../include/flagFunctions.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void flagD(FILE *inputFile, FILE *outputFile) {
    char c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (!isdigit(c)) {
            fputc(c, outputFile);
        }
    }
}

void flagI(FILE *inputFile, FILE *outputFile) {
    char line[1024];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            if (isalpha(line[i])) {
                count++;
            }
        }
        fprintf(outputFile, "%d\n", count);
    }
}

void flagS(FILE *inputFile, FILE *outputFile) {
    char line[1024];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++) {
            char c = line[i];
            if (!isalpha(c) && !isdigit(c) && !isspace(c)) {
                count++;
            }
        }
        fprintf(outputFile, "%d\n", count);
    }
}

void flagA(FILE *inputFile, FILE *outputFile) {
    char c;
    while ((c = fgetc(inputFile)) != EOF) {
        if (isdigit(c)) {
            fputc(c, outputFile);
        } else {
            fprintf(outputFile, "%02X", (unsigned char)c);
        }
    }
}