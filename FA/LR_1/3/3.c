#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/findRoot.h"
#include "include/isSidesTriangle.h"

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        printf("Usage: %s <flag> <...>\n", argv[0]);
        return 1;
    }

    char *flag = argv[1];

    if(flag[0] == '-' || flag[0] == '/'){
        switch (flag[1]){
        
        case 'q':
            if(argc == 6){
                char *endptr_eps, *endptr1, *endptr2, *endptr3;
                double epsilon = strtod(argv[2], &endptr_eps);
                double a = strtod(argv[3], &endptr1);
                double b = strtod(argv[4], &endptr2);
                double c = strtod(argv[5], &endptr3);

                if ((argv[2] == endptr_eps) && (argv[3] == endptr1) && (argv[4] == endptr2) && (argv[5] == endptr3)) {
                    printf("Invalid input data\n");
                } else {

                    double coeficients[] = {a, b, c};

                    double * roots;

                                                           // Понимаю что выглядит не очень, но лучше не придумал
                    for(int i = 0; i < 3; i++) {
                        for(int j = 0; j < 3; j++) {
                            for(int k = 0; k < 3; k++) {
                                if((i != j) && (i != k) && (k != j)){
                                    roots = findRoot(coeficients[i], coeficients[j], coeficients[k], epsilon);
                                    printf("Roots with a = %f, b = %f, c = %f : ", coeficients[i], coeficients[j], coeficients[k]);
                                    if(roots == NULL){
                                        printf("No roots\n");
                                    }else{
                                        for(int i = 0; i < roots[0]; i ++){
                                            printf("%f ", roots[i + 1]);
                                        }
                                        printf("\n");
                                    }
                                }
                            }
                        }
                    }

                    free(roots);
                }

            }else{
                printf("Invalid input data\n");
            }
            break;
        

        case 'm':
            if(argc == 4 && atoi(argv[2]) && atoi(argv[3])){
                int a = atoi(argv[2]);
                int b = atoi(argv[3]);

                if(a % b == 0){
                    printf("Divisible");
                }else{
                    printf("Not divisible");
                }
            }else{
                printf("When using flag '-m', you need to enter 2 non-zero integers");
            }
            break;


        case 't':
            if(argc == 6 && atof(argv[3]) && atof(argv[4]) && atof(argv[5])){
                double epsilon = atof(argv[2]);
                double a = atof(argv[3]);
                double b = atof(argv[4]);
                double c = atof(argv[5]);

                int isSides = isSidesTriangle(a, b, c, epsilon);
                
                if(isSides == -1){
                    printf("All numbers must be positive");
                } else if (isSides == 0){
                    printf("Cannot be sides of a right triangle");
                } else{
                    printf("Can be sides of a right triangle");
                }

            }else{
                printf("When using flag '-t', you need to enter 4 real numbers");
            }
            break;
        
        
        default:
            printf("Unknown flag");
            break;
        }
    }else{
        printf("Invalid flag format\n");
        return 1;
    }

    return 0;
}