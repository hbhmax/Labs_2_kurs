#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

double trapezoidal_method(double (*f)(double), double a, double b, double epsilon, int* iterations) {
    int n = 1;
    double h = (b - a) / n;
    double T_old = (f(a) + f(b)) * h / 2.0;
    double T_new;
    *iterations = 0;
    
    int max_iter = 1000000; // Защита от бесконечного цикла
    
    do {
        n *= 2;
        h = (b - a) / n;
        T_new = T_old / 2.0;
        
        for (int i = 1; i < n; i += 2) {
            double x = a + i * h;
            T_new += f(x) * h;
        }
        
        if (fabs(T_new - T_old) < epsilon) {
            *iterations = n;
            return T_new;
        }
        
        T_old = T_new;
        (*iterations)++;
    } while (*iterations < max_iter);
    
    *iterations = n;
    return T_new;
}


double f1(double x) {
    if (fabs(x) < 1e-15) {
        return 1.0; // предел при x->0
    }
    double result = log(1.0 + x) / x;
    
    // Проверка на переполнение
    if (!isfinite(result)) {
        return 1.0; // возвращаем предельное значение
    }
    return result;
}

double f2(double x) {
    double exponent = -x*x/2.0;
    
    // Проверка на переполнение экспоненты
    if (exponent < -700.0) {
        return 0.0; // e^(-большое число) ~ 0
    }
    
    return exp(exponent);
}

double f3(double x) {
    if (fabs(1.0 - x) < 1e-15) {
        // Обработка особенности в x=1
        // Можно вернуть большое число, но аккуратно
        return 1000.0; // приближенное значение
    }
    
    double result = -log(1.0 - x);
    
    // Проверка на переполнение
    if (!isfinite(result)) {
        return 1000.0; // возвращаем большое число
    }
    return result;
}

double f4(double x) {
    if (fabs(x) < 1e-15) {
        return 1.0; // предел при x->0+
    }
    
    double log_x = log(x);
    double exponent = x * log_x;
    
    // Проверка на переполнение
    if (!isfinite(exponent) || exponent > 700.0) {
        return 1.0; // возвращаем предельное значение
    }
    
    return exp(exponent);
}


double calculate_integral1(double epsilon) {
    int iterations;
    return trapezoidal_method(f1, 0.0, 1.0, epsilon, &iterations);
}

double calculate_integral2(double epsilon) {
    int iterations;
    return trapezoidal_method(f2, 0.0, 1.0, epsilon, &iterations);
}

double calculate_integral3(double epsilon) {
    int iterations;
    // Интегрируем до 0.9999 чтобы избежать особенности в x=1
    return trapezoidal_method(f3, 0.0, 0.9999, epsilon, &iterations);
}

double calculate_integral4(double epsilon) {
    int iterations;
    return trapezoidal_method(f4, 0.0, 1.0, epsilon, &iterations);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <epsilon>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    double epsilon = strtod(argv[1], &endptr);
    
    if (*endptr != '\0' || epsilon <= 0.0) {
        printf("Error: epsilon must be a positive real number\n");
        return 1;
    }
    
    double result1 = calculate_integral1(epsilon);
    double result2 = calculate_integral2(epsilon);
    double result3 = calculate_integral3(epsilon);
    double result4 = calculate_integral4(epsilon);
    
    printf("a) integral( ln(1+x)/x dx ) = %.10f\n", result1);
    printf("b) integral( e^(-(x^2)/2) dx ) = %.10f\n", result2);
    printf("c) integral( ln(1/(1-x)) dx ) = %.10f\n", result3);
    printf("d) integral( x^x dx ) = %.10f\n", result4);
    
    return 0;
}