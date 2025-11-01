#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#define MAX_ITER 10000

void check_finite_representation(int base, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);

        if (num <= 0.0 || num >= 1.0) {
            printf("Number %f not in range (0,1)\n", num);
            continue;
        }

        int denominator = 1;
        double temp = num;

        while (fabs(temp - round(temp)) > 0) {
            temp *= 10;
            denominator *= 10;
        }

        int numerator = (int)round(temp);

        int is_finite = 0;
        int a = numerator;
        int b = denominator;

        for (int i = 0; i < MAX_ITER; i++) {
            if (a == 0) {
                is_finite = 1;
                break;
            }
            if (a >= b) {
                while (a >= b){
                    a -= b;
                }
                a *= base;
            } else {
                a *= base;
            }
        }

        if (is_finite) {
            printf("Number %f in base %d has finite representation\n", num, base);
        } else {
            printf("Number %f in base %d has no finite representation\n", num, base);
        }
    }

    va_end(args);
}

int main() {
    check_finite_representation(2, 3, 0.5, -0.5, 0.21);
    printf("\n");
    check_finite_representation(3, 2, 0.2, 0.333333);
    printf("\n");
    check_finite_representation(8, 4, 0.2, 0.25, 0.125, 0.1);

    return 0;
}
