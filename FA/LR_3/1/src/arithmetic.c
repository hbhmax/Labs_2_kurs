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

int multiply(int a, int b) {
    int result = 0;
    int negative = 0;
    
    if (a < 0) {
        a = negate(a);
        negative = !negative;
    }
    if (b < 0) {
        b = negate(b);
        negative = !negative;
    }
    
    for (int i = 0; i < b; i = add(i, 1)) {
        result = add(result, a);
    }
    
    return negative ? negate(result) : result;
}

int divide(int a, int b) {
    if (b == 0) return 0;
    
    int quotient = 0;
    while (a >= b) {
        a = subtract(a, b);
        quotient = add(quotient, 1);
    }
    return quotient;
}

void convert_to_base(int n, int r, char *result) {
    if (r < 1 || r > 5) {
        strcpy(result, "Error: r should be between 1 and 5");
        return;
    }
    
    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char temp[65] = {0};
    int pos = 0;
    int is_negative = 0;

    if (n == 0) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }
    
    if (n < 0) {
        n = negate(n);
        is_negative = 1;
    }
    
    int B = 1;
    for (int i = 0; i < r; i = add(i, 1)) {
        B = multiply(B, 2);
    }
    
    while (n > 0) {
        int remainder = subtract(n, multiply(B, divide(n, B)));
        temp[pos] = digits[remainder];
        pos = add(pos, 1);
        
        n = divide(n, B);
    }
    
    if (is_negative) {
        temp[pos] = '-';
        pos = add(pos, 1);
    }
    
    int i = 0;
    while (i != pos) {
        result[i] = temp[subtract(subtract(pos, 1), i)];
        i = add(i, 1);
    }
    result[pos] = '\0';
}

