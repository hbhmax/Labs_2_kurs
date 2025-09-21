#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num) {
    
    if (num % 2 == 0 || num % 3 == 0) return false;
    
    for (int i = 5; i * i <= num; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int findPrimeNumber(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 2;
    if (n == 2) return 3;
    
    int count = 2;

    int mn = 1;
    while(count != n){
        if(isPrime(6 * mn - 1)){
            count++;
            if(count == n){
                return 6 * mn - 1;
            }
        }
        if(isPrime(6 * mn + 1)){
            count++;
            if(count == n){
                return 6 * mn + 1;
            }
        }
        mn++;
    }
    
}

int main(int argc, char const *argv[]) {
    int count = 0;
    printf("Vvedite kolichestvo chisel: ");
    scanf("%d", &count);
    
    if (count <= 0) {
        printf("Kolichestvo dolzhno byt polozhitelnym chislom\n");
        return 1;
    }
    
    int numbers[count];

    printf("Vvedite poryadkovye nomera prostyh chisel:\n");

    for(int i = 0; i < count; i++) {
        int n = 0;
        scanf("%d", &n);
        
        if (n <= 0) {
            printf("Nomer dolzhen byt polozhitelnym chislom\n");
            numbers[i] = -1;
        } else {
            numbers[i] = findPrimeNumber(n);
        }
    }

    printf("--------------\n");

    for(int i = 0; i < count; i++) {
        if (numbers[i] == -1) {
            printf("%d: Nevernyj nomer\n", i + 1);
        } else {
            printf("%d: %d\n", i + 1, numbers[i]);
        }
    }
    
    return 0;
}