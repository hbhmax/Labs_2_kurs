#include <stdio.h>
#include <string.h>

const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

char* to_base_2r(unsigned n, int r) {
    static char buffer[33];
    char *ptr = &buffer[32];
    *ptr = '\0';

    if (n == 0) {
        *--ptr = '0';
        return ptr;
    }

    unsigned mask = (1u << r) - 1;
    while (n != 0) {
        unsigned digit = n & mask;
        *--ptr = digits[digit];
        n = n >> r;
    }

    return ptr;
}

int main() {
    unsigned numbers[] = {0, 1, 255, 256, 1023, 1024, 12345, 65535, 4294967295};
    int r_values[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        for (int j = 0; j < sizeof(r_values) / sizeof(r_values[0]); j++) {
            printf("Number %u in base 2^%d (%d): %s\n",
                   numbers[i], r_values[j], 1 << r_values[j],
                   to_base_2r(numbers[i], r_values[j]));
        }
        printf("\n");
    }

    return 0;
}