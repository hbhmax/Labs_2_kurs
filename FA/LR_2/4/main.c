#include <stdio.h>
#include <stdlib.h>
#include "include/functions.h"

int main() {
    int num1;
    unsigned int num2;
    int num3;
    int num4;

    oversscanf("XIV", "%Ro", &num1);
    printf("Roman: %d\n", num1);

    oversscanf("1011", "%Zr", &num2);
    printf("Zeckendorf: %u\n", num2);

    oversscanf("1a", "%Cv", &num3, 16);
    printf("Base (lower): %d\n", num3);

    oversscanf("1A", "%CV", &num4, 16);
    printf("Base (upper): %d\n", num4);

    FILE *file1 = fopen("files/1.txt", "r");
    FILE *file2 = fopen("files/2.txt", "r");
    FILE *file3 = fopen("files/3.txt", "r");
    FILE *file4 = fopen("files/4.txt", "r");
    
    if (file1) {
        overfscanf(file1, "%Ro", &num1);
        printf("Roman from file: %d\n", num1);
        fclose(file1);
    }
    
    if (file2) {
        overfscanf(file2, "%Zr", &num2);
        printf("Zeckendorf from file: %u\n", num2);
        fclose(file2);
    }

    if (file3) {
        overfscanf(file3, "%Cv", &num3, 16);
        printf("Base (lower) from file: %d\n", num3);
        fclose(file3);
    }
    
    if (file4) {
        overfscanf(file4, "%CV", &num4, 16);
        printf("Base (upper) from file: %d\n", num4);
        fclose(file4);
    }
    
    return 0;
}