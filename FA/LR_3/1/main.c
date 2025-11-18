#include <stdio.h>
#include <string.h>
#include "include/arithmetic.h"


int main() {
    char result[65];

    convert_to_base(255, 1, result);
    printf("255 in 2: %s\n", result);

    convert_to_base(255, 2, result);
    printf("255 in 4: %s\n", result);

    convert_to_base(255, 3, result);
    printf("255 in 8: %s\n", result);

    convert_to_base(255, 4, result);
    printf("255 in 16: %s\n", result);

    convert_to_base(255, 5, result);
    printf("255 in 32: %s\n", result);

    return 0;
}