#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int factorial(int x){
    if(x == 1 || x == 0){
        return 1;
    }
    return x * factorial(x - 1);
}

void hex(int x){

    int c4 = 0;
    int len = x;
    while (len < 0){
        len /= 16;
        c4 += 1;
    }
                
    char hex_chislo[len];
    for (int i = 0; i < len; i++) {
        int digit = x % 16;
        if (digit < 10) {
            hex_chislo[i] = '0' + digit;
        } else {
            hex_chislo[i] = 'A' + (digit - 10);
        }
        x /= 16;
    }
    
    int leading_zero = 1;
    for (int i = len - 1; i >= 0; i--) {
        if (hex_chislo[i] != '0' || !leading_zero) {
            printf("%c ", hex_chislo[i]);
            leading_zero = 0;
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <number> <flag>\n", argv[0]);
        return 1;
    }

    int x = atoi(argv[1]);
    char *flag = argv[2];

    if(flag[0] == '-' || flag[0] == '/'){
        switch (flag[1]){

            case 'h':
                int c1 = 0;
                for(int i = 1; i <= 100; i++){
                    if(i % x == 0){
                        printf("%d ", i);
                        c1++;
                    }
                }
                if (c1 == 0){
                    printf("Net chisel kratnyh x");
                }
                printf("\n");
                break;

            case 'p':
                if(x == 2 || x == 1) {
                    printf("Prostoe\n");
                    break;
                }
                if(x % 2 == 0) {
                    printf("Sostavnoe\n");
                    break;
                }
                
                int c2 = 0;
                for(int i = 3; i <= sqrt(x); i += 2){
                    if(x % i == 0){
                        c2 = 1;
                        break;
                    }
                }
                if(c2 == 1){
                    printf("Sostavnoe\n");
                }else{
                    printf("Prostoe\n");
                }
                break;

            case 's':
                if(x == 0){
                    printf("0/n");
                    break;
                }

                hex(x);
                break;

            case 'e':
                if(x > 10) {
                    printf("x dolzhen byt ne bolshe 10\n");
                    break;
                }
                for(int i = 1; i <= 10; i++){
                    for(int j = 1; j <= x; j++){
                        printf("%.0f ", pow(i, j));
                    }
                    printf("\n");
                }
                break;

            case 'a':
                int c3 = 0;
                for(int i = 1; i <= x; i++){
                    c3 += i;
                }
                printf("%d", c3);
                break;

            case 'f':
                printf("%d", factorial(x));
                break;

            default:
                printf("Nezvestny flag");
                break;
        }
    } else {
        printf("Ne pravilno vveli flag\n");
        return 1;
    }

    return 0;
}

