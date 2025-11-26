#include <stdio.h>
#include <string.h>
#include "include/arithmetic.h"


int main() {
    char result[65];
    int count = 0;
    int number;
    int degreeBase;

    printf("Enter the count of tests:\n");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        printf("Enter the number and degree of base:          (example: \"16 3\")  ->  16 in base 2^3\n");
        scanf("%d %d", &number, &degreeBase);
        convert_to_base(number, degreeBase, result);
        printf("%s\n", result);
    }

    return 0;
}