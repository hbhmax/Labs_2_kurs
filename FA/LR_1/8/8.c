#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char * convertInNumberSystem(long number, int ss) {
    if (ss < 2 || ss > 36) {
        return NULL;
    }
    
    if (number == 0) {
        char *result = malloc(2 * sizeof(char));
        strcpy(result, "0");
        return result;
    }
    
    int isNegative = 0;
    if (number < 0) {
        isNegative = 1;
        number = -number;
    }
    
    long temp = number;
    int length = 0;
    while (temp > 0) {
        temp /= ss;
        length++;
    }
    
    char *result = malloc((length + isNegative + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    int index = length + isNegative;
    result[index] = '\0';
    
    temp = number;
    do {
        int digit = temp % ss;
        char c;
        if (digit < 10) {
            c = '0' + digit;
        } else {
            c = 'A' + (digit - 10);
        }
        
        result[--index] = c;
        temp /= ss;
    } while (temp > 0);
    
    if (isNegative) {
        result[0] = '-';
    }
    
    return result;
}


int main(int argc, char const *argv[]) {
    int ss = 0;
    printf("Input number system: ");
    scanf("%d", &ss);

    int size = 10;
    int c = 0;
    long * massiveNumbers = malloc(size * sizeof(long));
    char number[100];

    printf("Input numbers in your number system: \n");
    while (1) {
        char *endptr;
        scanf("%s", number);

        if (strcmp(number, "Stop") == 0) {
            break;
        }

        if (c >= size) {
            size *= 2;
            massiveNumbers = realloc(massiveNumbers, size * sizeof(long));
        }

        long n = strtol(number, &endptr, ss);
        if (endptr == number || *endptr != '\0') {
            printf("Incorrect input\n");
        } else {
            massiveNumbers[c] = n;
            c++;
        }
    }

    long max_number = fabs(massiveNumbers[0]);
    for(int i = 1; i < c; i++) {
        if(max_number < fabs(massiveNumbers[i])){
            max_number = fabs(massiveNumbers[i]);
        }
    }

    char * max_nach_ss = convertInNumberSystem(max_number, ss);
    char * max_9_ss = convertInNumberSystem(max_number, 9);
    char * max_18_ss = convertInNumberSystem(max_number, 18);
    char * max_27_ss = convertInNumberSystem(max_number, 27);
    char * max_36_ss = convertInNumberSystem(max_number, 36);

    printf("Max number: %s\n", max_nach_ss);
    printf("Max number in 9 number system: %s\n", max_9_ss);
    printf("Max number in 18 number system: %s\n", max_18_ss);
    printf("Max number in 27 number system: %s\n", max_27_ss);
    printf("Max number in 36 number system: %s\n", max_36_ss);



    free(massiveNumbers);
    return 0;
}