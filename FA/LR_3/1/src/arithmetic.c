#include <stdio.h>
#include <string.h>

int add(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

int negate(int x) {
    return add(~x, 1);
}

int subtract(int a, int b) {
    return add(a, negate(b));
}

int divide(int a, int b) {
    if (b == 0) return 0;
    int quotient = 0;
    int remainder = a;
    for (int k = 31; k >= 0; k--) {
        if (remainder >= (b << k) && (b << k) > 0) {
            remainder = subtract(remainder, b << k);
            quotient = add(quotient, 1 << k);
        }
    }
    return quotient;
}

void convert_to_base(int n, int r, char *result) {
    if (r < 1 || r > 5) {
        strcpy(result, "Error: r should be between 1 and 5");
        return;
    }
    if (n == 0) {
        strcpy(result, "0");
        return;
    }

    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char temp[65] = {0};
    int pos = 0;

    int B = 1 << r;

    while (n > 0) {
        int remainder = n & (B - 1);
        temp[pos++] = digits[remainder];

        n = n >> r;
    }

    for (int i = 0; i < pos; i++) {
        result[i] = temp[pos - 1 - i];
    }
    result[pos] = '\0';
}
