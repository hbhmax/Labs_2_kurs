#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MINIMAL_EPSILON 0.0000001

double integral_1(double epsilon){

    double summa = 0;

    if (epsilon < MINIMAL_EPSILON){
        epsilon = MINIMAL_EPSILON;
    }

    for(double i = epsilon; i <= 1 - epsilon; i += epsilon){
        summa += log(1 + i) / i;
    }

    return epsilon * (summa);
}

double integral_2(double epsilon){

    double summa = 0;

    if (epsilon < MINIMAL_EPSILON){
        epsilon = MINIMAL_EPSILON;
    }

    for(double i = epsilon; i <= 1 - epsilon; i += epsilon){
        summa += exp(-(pow(i, 2)) / 2);
    }

    return epsilon * (summa);
}

double integral_3(double epsilon){
    double summa = 0;

    if (epsilon < MINIMAL_EPSILON){
        epsilon = MINIMAL_EPSILON;
    }

    for(double i = epsilon; i <= 1 - epsilon; i += epsilon){
        summa += log(1 / (1 - i));
    }

    return epsilon * (summa);
}

double integral_4(double epsilon){
    double summa = 0;

    if (epsilon < MINIMAL_EPSILON){
        epsilon = MINIMAL_EPSILON;
    }

    for(double i = epsilon; i <= 1 - epsilon; i += epsilon){
        summa += pow(i, i);
    }

    return epsilon * (summa);
}


int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Usage: %s <epsilon>\n", argv[0]);
        return -1;
    }

    char *endptr_eps;
    double epsilon = strtod(argv[1], &endptr_eps);
    
    if (argv[1] == endptr_eps) {
        printf("Invalid input data\n");
    } else {
        double c1 = integral_1(epsilon);
        double c2 = integral_2(epsilon);
        double c3 = integral_3(epsilon);
        double c4 = integral_4(epsilon);

        printf("1: %f\n2: %f\n3: %f\n4: %f\n", c1, c2, c3, c4);
    }

    return 0;
}
