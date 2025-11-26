#include <stdio.h>
#include <stdlib.h>
#include "include/functions.h"

int main() {
    int num1;
    unsigned int num2;
    int num3;
    int num4;

    oversscanf("XX6", "%Ro%d", &num1, &num2);
    printf("Roman: %d            %d\n", num1, num2);

    oversscanf("10100011", "%Zr", &num2);
    printf("Zeckendorf: %u\n", num2);

    oversscanf("1a", "%Cv %d", &num3, 16);
    printf("Base (lower): %d\n", num3);

    oversscanf("1A", "%CV", &num4, 16);
    printf("Base (upper): %d\n", num4);

    FILE *file1 = fopen("files/1.txt", "r");
    FILE *file2 = fopen("files/2.txt", "r");
    FILE *file3 = fopen("files/3.txt", "r");
    FILE *file4 = fopen("files/4.txt", "r");

    if (file1 == NULL) {
        perror("Error input file 1.txt");
        return EXIT_FAILURE;
    }
    if (file2 == NULL) {
        perror("Error input file 2.txt");
        return EXIT_FAILURE;
    }
    if (file3 == NULL) {
        perror("Error input file 3.txt");
        return EXIT_FAILURE;
    }
    if (file4 == NULL) {
        perror("Error input file 4.txt");
        return EXIT_FAILURE;
    }


    if (file1) {
        overfscanf(file1, "%Ro%d", &num1, &num2);
        printf("Roman from file: %d         %d\n", num1, num2);
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