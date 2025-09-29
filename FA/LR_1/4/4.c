#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_ITER 10000000

double factorial(int n){
    if(n == 1 || n == 0){
        return 1;
    }
    return n * factorial(n - 1);
}

double power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}


//---------------------------------------------------------------------------

double e_limit(double epsilon) {
    double n = 1.0;
    double prev = 0.0;
    double current = 2.0;
    
    for (int i = 0; i < MAX_ITER; i++) {
        prev = current;
        n *= 2.0;
        current = pow(1.0 + 1.0/n, n);
        
        if (fabs(current - prev) < epsilon) {
            return current;
        }
    }
    return current;
}

double e_series(double epsilon) {
    double sum = 1.0;
    double term = 1.0;
    
    for (int n = 1; n < MAX_ITER; n++) {
        term = 1 / factorial(n);
        sum += term;
        
        if (term < epsilon) {
            return sum;
        }
    }
    return sum;
}

double e_equation(double epsilon) {
    double x = 2.0; // Начальное приближение
    double prev_x;
    
    for (int i = 0; i < MAX_ITER; i++) {
        prev_x = x;
        // f(x) = ln(x) - 1, f'(x) = 1/x
        // x_{n+1} = x_n - f(x_n)/f'(x_n)
        x = x - (log(x) - 1.0) * x;
        
        if (fabs(x - prev_x) < epsilon) {
            return x;
        }
    }
    return x;
}

//---------------------------------------------------------------------------

double pi_limit(double epsilon) {
    double n = 1.0;
    double prev = 0.0;
    double current = 4.0;
    
    for (int i = 0; i < 47; i++) {
        prev = current;
        n += 1.0;
        
        double numerator = pow(2.0, n) * factorial(n);
        numerator = pow(numerator, 4);
        double denominator = n * pow(factorial(2 * (int)n), 2);
        current = numerator / denominator;
        
        if (fabs(current - prev) < epsilon) {
            return current;
        }
    }
    return current;
}

double pi_series(double epsilon) {
    double sum = 0.0;
    double term;
    
    for (int n = 1; n < MAX_ITER; n++) {
        if((n - 1) % 2 == 0){
            term = 1.0;
        }else{
            term = -1.0;
        }
        term /= (2 * n - 1);
        sum += term;
        
        if (fabs(term) < epsilon) {
            return 4.0 * sum;
        }
    }
    return 4.0 * sum;
}

double pi_equation(double epsilon) {
    double x = 3.0; // Начальное приближение
    double prev_x;
    
    for (int i = 0; i < MAX_ITER; i++) {
        prev_x = x;
        // f(x) = cos(x) + 1, f'(x) = -sin(x)
        // x_{n+1} = x_n - f(x_n)/f'(x_n)
        x = x + (cos(x) + 1.0) / sin(x);
        
        if (fabs(x - prev_x) < epsilon) {
            return x;
        }
    }
    return x;
}

//---------------------------------------------------------------------------

double ln2_limit(double epsilon) {
    double n = 1.0;
    double prev = 0.0;
    double current = 1.0;
    
    for (int i = 0; i < MAX_ITER; i++) {
        prev = current;
        n += 1.0;
        current = n * (pow(2.0, 1.0/n) - 1.0);
        
        if (fabs(current - prev) < epsilon) {
            return current;
        }
    }
    return current;
}

double ln2_series(double epsilon) {
    double sum = 0.0;
    double term;
    
    for (int n = 1; n < MAX_ITER; n++) {
        if((n-1) % 2 == 0){
            term = 1.0;
        }else{
            term = -1.0;
        }
        term /= n;
        sum += term;
        
        if (fabs(term) < epsilon) {
            return sum;
        }
    }
    return sum;
}

double ln2_equation(double epsilon) {
    double x = 0.7; // Начальное приближение
    double prev_x;
    
    for (int i = 0; i < MAX_ITER; i++) {
        prev_x = x;
        // f(x) = e^x - 2, f'(x) = e^x
        // x_{n+1} = x_n - f(x_n)/f'(x_n)
        double exp_x = exp(x);
        x = x - (exp_x - 2.0) / exp_x;
        
        if (fabs(x - prev_x) < epsilon) {
            return x;
        }
    }
    return x;
}

//---------------------------------------------------------------------------

double sqrt2_limit(double epsilon) {
    double x = -0.5;
    double prev_x;
    
    for (int i = 0; i < MAX_ITER; i++) {
        prev_x = x;
        x = x - (x * x) / 2.0 + 1.0;
        
        if (fabs(x - prev_x) < epsilon) {
            return x;
        }
    }
    return x;
}

double sqrt2_series(double epsilon) {
    double product = 1.0;
    double term;
    double prev_product = 0.0;
    
    for (int k = 2; k < MAX_ITER; k++) {
        term = pow(2.0, pow(2.0, -k));
        product *= term;
        
        if (fabs(product - prev_product) < epsilon) {
            return product;
        }
        prev_product = product;
    }
    return product;
}

double sqrt2_equation(double epsilon) {
    double x = 1.5; // Начальное приближение
    double prev_x;
    
    for (int i = 0; i < MAX_ITER; i++) {
        prev_x = x;
        // f(x) = x^2 - 2, f'(x) = 2x
        // x_{n+1} = x_n - f(x_n)/f'(x_n)
        x = x - (x * x - 2.0) / (2.0 * x);
        
        if (fabs(x - prev_x) < epsilon) {
            return x;
        }
    }
    return x;
}

//---------------------------------------------------------------------------

double gamma_limit(double epsilon) {
    double prev = 0.0;
    double current = 0.0;
    
    for (int m = 1; m < 48; m++) {
        double sum = 0.0;
        
        for (int k = 1; k <= m; k++) {
            double binom = factorial(m) / (factorial(k) * factorial(m - k));
            double term = binom * log(factorial(k)) / k;
            
            if (k % 2 == 1) {
                term = -term;
            }
            sum += term;
        }

        prev = current;
        current = sum;
        
        if (m > 1 && fabs(current - prev) < epsilon) {
            return current;
        }
    }
    return current;
}

double gamma_series(double epsilon) {
    double pi = pi_equation(epsilon);
    double sum = 0.0;
    double term;
    
    for (int k = 2; k < MAX_ITER; k++) {
        int floor_sqrt_k = (int)sqrt(k);
        term = (1.0 / (floor_sqrt_k * floor_sqrt_k)) - (1.0 / k);
        sum += term;
    }
    return (-(pi * pi) / 6.0) + sum;
}

double gamma_equation(double epsilon) {
    double product = 1.0;
    double prev_current = 0.0;
    int prev_t = 1;
    
    for (int t = 2; t <= MAX_ITER; t *= 2) {
        for (int p = prev_t + 1; p <= t; p++) {
            if (is_prime(p)) {
                product *= (p - 1.0) / p;
            }
        }
        
        double current = log(t) * product;
        
        if (prev_t > 1 && fabs(current - prev_current) < epsilon) {
            return -log(current);
        }
        
        prev_current = current;
        prev_t = t;
    }
    
    return -log(prev_current);
}

int main() {
    double epsilon = pow(10, -6);
        
    printf("e = %.6f (limit)\n", e_limit(epsilon));
    printf("e = %.6f (series)\n", e_series(epsilon));
    printf("e = %.6f (equation)\n\n", e_equation(epsilon));
    
    printf("pi = %.6f (limit)\n", pi_limit(epsilon));
    printf("pi = %.6f (series)\n", pi_series(epsilon));
    printf("pi = %.6f (equation)\n\n", pi_equation(epsilon));
    
    printf("ln2 = %.6f (limit)\n", ln2_limit(epsilon));
    printf("ln2 = %.6f (series)\n", ln2_series(epsilon));
    printf("ln2 = %.6f (equation)\n\n", ln2_equation(epsilon));
    
    printf("sqrt(2) = %.6f (limit)\n", sqrt2_limit(epsilon));
    printf("sqrt(2) = %.6f (series)\n", sqrt2_series(epsilon));
    printf("sqrt(2) = %.6f (equation)\n\n", sqrt2_equation(epsilon));
    
    printf("y = %.6f (limit)\n", gamma_limit(epsilon));
    printf("y = %.6f (series)\n", gamma_series(epsilon));
    printf("y = %.6f (equation)\n", gamma_equation(epsilon));
    
    return 0;
}