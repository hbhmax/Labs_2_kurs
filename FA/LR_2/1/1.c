#include <stdio.h>

void check_finite_representation(int base, double num) {
    if (num <= 0.0 || num >= 1.0) {
        printf("Number %f not in range (0,1)\n", num);
        return;
    }

    double temp = num;
    int is_finite = 0;
    
    for (int iter = 0; iter < 1000; iter++) {
        temp = temp * base;
        int int_part = (int)temp;
        double frac_part = temp - int_part;
        
        if (frac_part < 0.000000000001 && frac_part > -0.000000000001) {
            is_finite = 1;
            break;
        }
        temp = frac_part;
    }

    printf("Number %f in base %d %sfinite representation\n",
           num, base, is_finite ? "has " : "has no ");
}

int main() {
    check_finite_representation(2, 0.5);
    check_finite_representation(2, 0.1);
    check_finite_representation(2, 0.25);
    printf("\n");
    check_finite_representation(3, 0.2);
    check_finite_representation(3, 0.333333);
    
    return 0;
}