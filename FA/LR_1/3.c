#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printKoreni(double a, double b, double c, double epsilon){
    double d = b * b - 4 * a * c;
    if(d < -epsilon){
        printf("Net korney\n");
    }else if(fabs(d) < epsilon){
        double x = -b / (2 * a);
        printf("Odin koren x = %.5f\n", x);
    }else{
        double x1 = (-b + sqrt(d)) / (2 * a);
        double x2 = (-b - sqrt(d)) / (2 * a);
        printf("Korni: x1 = %.5f, x2 = %.5f\n", x1, x2);
    }
}

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
            if(argc == 6 && atof(argv[3]) && atof(argv[4]) && atof(argv[5])){
                double epsilon = atof(argv[2]);
                double a = atof(argv[3]);
                double b = atof(argv[4]);
                double c = atof(argv[5]);

                printf("a = %.5f, b = %.5f, c = %.5f :\n", a, b, c);
                printKoreni(a, b, c, epsilon);

                printf("a = %.5f, b = %.5f, c = %.5f : \n", a, c, b);
                printKoreni(a, c, b, epsilon);

                printf("a = %.5f, b = %.5f, c = %.5f : \n", b, a, c);
                printKoreni(b, a, c, epsilon);

                printf("a = %.5f, b = %.5f, c = %.5f : \n", b, c, a);
                printKoreni(b, c, a, epsilon);

                printf("a = %.5f, b = %.5f, c = %.5f : \n", c, b, a);
                printKoreni(c, b, a, epsilon);

                printf("a = %.5f, b = %.5f, c = %.5f : \n", c, a, b);
                printKoreni(c, a, b, epsilon);
                
            }else{
                printf("Esli vy ispolzuete flag '-t', to nuzhno vvesti 4 veshestvennyh chisla");
            }
            break;
        

        case 'm':
            if(argc == 4 && atoi(argv[2]) && atoi(argv[3])){
                int a = atoi(argv[2]);
                int b = atoi(argv[3]);

                if(a % b == 0){
                    printf("Kratno");
                }else{
                    printf("Ne kratno");
                }
            }else{
                printf("Esli vy ispolzuete flag '-m', to nuzhno vvesti 2 nenulevyh celyh chisla");
            }
            break;


        case 't':
            if(argc == 6 && atof(argv[3]) && atof(argv[4]) && atof(argv[5])){
                double epsilon = atof(argv[2]);
                double a = atof(argv[3]);
                double b = atof(argv[4]);
                double c = atof(argv[5]);

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
                    printf("Mogut yavlyatsya storonami pryamougolnogo treugolnika");
                }else{
                    printf("Ne mogut yavlyatsya storonami pryamougolnogo treugolnika");
                }

            }else{
                printf("Esli vy ispolzuete flag '-t', to nuzhno vvesti 4 veshestvennyh chisla");
            }
            break;
        
        
        default:
            printf("Nezvestny flag");
            break;
        }
    }else{
        printf("Ne pravilno vveli flag\n");
        return 1;
    }


    return 0;
}
