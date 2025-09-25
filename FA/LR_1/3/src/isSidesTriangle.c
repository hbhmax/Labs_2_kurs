#include "../include/isSidesTriangle.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int isSidesTriangle(double a, double b, double c, double epsilon) {
    if((a < 0) || (b < 0) || (c < 0)){
        return -1;
    }

    double temp;

    if(b > c){
        temp = b;
        b = c;
        c = temp;
    }

    if(a > c){
        temp = a;
        a = c;
        c = temp;
    }

    if((a * a + b * b - c * c <= epsilon) && (-epsilon <= a * a + b * b - c * c)){
        return 1;
    }else{
        return 0;
    }
}