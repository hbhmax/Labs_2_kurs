#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

void int_to_string(int num, char *result) {
    if (num == 0) {
        strcpy(result, "0");
        return;
    }
    
    char buffer[65];
    int index = 0;
    int is_negative = 0;
    
    unsigned int n;
    if (num < 0) {
        is_negative = 1;
        n = (unsigned int)(-num);
    } else {
        n = (unsigned int)num;
    }
    
    while (n > 0) {
        buffer[index++] = '0' + (n % 10);
        n /= 10;
    }
    
    if (is_negative) {
        buffer[index++] = '-';
    }
    
    buffer[index] = '\0';
    int result_index = 0;
    for (int i = index - 1; i >= 0; i--) {
        result[result_index++] = buffer[i];
    }
    result[result_index] = '\0';
}

void byte_to_binary(unsigned char byte, char *result) {
    for (int i = 0; i < 8; i++) {
        result[i] = (byte & 128) ? '1' : '0';
        byte <<= 1;
    }
    result[8] = '\0';
}

void dump_memory(const void *data, size_t size, char *result) {
    const unsigned char *bytes = (const unsigned char *)data;
    result[0] = '\0';
    char temp[256] = "";

    for (size_t i = 0; i < size; i++) {
        char binary[9];
        byte_to_binary(bytes[i], binary);

        if (i > 0) {
            strcat(temp, " ");
        }
        strcat(temp, binary);
    }
    strcpy(result, temp);
}

const char *roman_symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
const int roman_values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
#define ROMAN_COUNT 13

const unsigned int fib_values[] = {
    1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597,
    2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418,
    317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465
};
#define FIB_COUNT 34

void task_a(unsigned int num, char *result) { 
    result[0] = '\0';
    for (int i = 0; i < ROMAN_COUNT; i++) {
        while (num >= roman_values[i]) {
            strcat(result, roman_symbols[i]);
            num -= roman_values[i];
        }
    }
}

void task_b(int num, char *result) {
    if (num < 0) {
        strcpy(result, "");
        return;
    }
    if (num == 0) {
        strcpy(result, "01");
        return;
    }

    int coeffs[FIB_COUNT] = {0};
    int i = FIB_COUNT - 1;

    while (i >= 0 && num > 0) {
        if (num >= fib_values[i]) {
            coeffs[i] = 1;
            num -= fib_values[i];
            i -= 2;
        } else {
            i--;
        }
    }

    int k = FIB_COUNT - 1;
    while (coeffs[k] == 0) {
        k--;
    }
    

    result[0] = '\0';
    for (int j = 0; j < k + 1; j++) {
        char c = coeffs[j] ? '1' : '0';
        strncat(result, &c, 1);
    }
    strncat(result, "1", 1);
}

void task_c(int num, int base, char *result) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    
    if (num == 0) {
        strcpy(result, "0");
        return;
    }
    
    char buffer[65];
    int index = 0;
    int is_negative = 0;
    
    unsigned int n;
    if (num < 0) {
        is_negative = 1;
        n = (unsigned int)(-num);
    } else {
        n = (unsigned int)num;
    }
    
    while (n > 0) {
        int digit = n % base;
        if (digit < 10) {
            buffer[index++] = '0' + digit;
        } else {
            buffer[index++] = 'a' + (digit - 10);
        }
        n /= base;
    }
    
    if (is_negative) {
        buffer[index++] = '-';
    }
    
    buffer[index] = '\0';
    int result_index = 0;
    for (int i = index - 1; i >= 0; i--) {
        result[result_index++] = buffer[i];
    }
    result[result_index] = '\0';
}

void task_d(int num, int base, char *result) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    
    if (num == 0) {
        strcpy(result, "0");
        return;
    }
    
    char buffer[65];
    int index = 0;
    int is_negative = 0;
    
    unsigned int n;
    if (num < 0) {
        is_negative = 1;
        n = (unsigned int)(-num);
    } else {
        n = (unsigned int)num;
    }
    
    while (n > 0) {
        int digit = n % base;
        if (digit < 10) {
            buffer[index++] = '0' + digit;
        } else {
            buffer[index++] = 'A' + (digit - 10);
        }
        n /= base;
    }
    
    if (is_negative) {
        buffer[index++] = '-';
    }
    
    buffer[index] = '\0';
    int result_index = 0;
    for (int i = index - 1; i >= 0; i--) {
        result[result_index++] = buffer[i];
    }
    result[result_index] = '\0';
}

void task_e(char *num, int base, char *result) {

    if (base < 2 || base > 36) {
        base = 10;
    }
    
    if (num == NULL || num[0] == '\0') {
        strcpy(result, "0");
        return;
    }
    
    int value = 0;
    int sign = 1;
    int i = 0;
    
    if (num[0] == '-') {
        sign = -1;
        i = 1;
    }
    
    for (; num[i] != '\0'; i++) {
        char c = num[i];
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            break;
        }
        
        if (digit >= base) {
            break;
        }
        
        value = value * base + digit;
    }
    
    value *= sign;
    
    int_to_string(value, result);
}

void task_f(char *num, int base, char *result) {

    if (base < 2 || base > 36) {
        base = 10;
    }
    
    if (num == NULL || num[0] == '\0') {
        strcpy(result, "0");
        return;
    }
    
    int value = 0;
    int sign = 1;
    int i = 0;
    
    if (num[0] == '-') {
        sign = -1;
        i = 1;
    }
    
    for (; num[i] != '\0'; i++) {
        char c = num[i];
        int digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else {
            break;
        }
        
        if (digit >= base) {
            break;
        }
        
        value = value * base + digit;
    }
    
    value *= sign;
    
    int_to_string(value, result);
}

void task_g(int num, char *result) {
    dump_memory(&num, sizeof(int), result);
}

void task_h(unsigned int num, char *result) {
    dump_memory(&num, sizeof(unsigned int), result);
}

void task_i(double num, char *result) {
    dump_memory(&num, sizeof(double), result);
}

void task_j(float num, char *result) {
    dump_memory(&num, sizeof(float), result);
}

typedef struct {
    const char *flag;
    int arg_count;
    union {
        void (*converter1)(int, char*);
        void (*converter2)(int, int, char*);
        void (*converter3)(char*, int, char*);
        void (*converter4)(unsigned int, char*);
        void (*converter5)(double, char*);
        void (*converter6)(float, char*);
    } conv;
} CustomFlag;

const CustomFlag custom_flags[] = {
    {"%Ro", 1, { .converter4 = task_a }},
    {"%Zr", 1, { .converter1 = task_b }},
    {"%Cv", 2, { .converter2 = task_c }},
    {"%CV", 2, { .converter2 = task_d }},
    {"%to", 2, { .converter3 = task_e }},
    {"%TO", 2, { .converter3 = task_f }},
    {"%mi", 1, { .converter1 = task_g }},
    {"%mu", 1, { .converter4 = task_h }},
    {"%md", 1, { .converter5 = task_i }},
    {"%mf", 1, { .converter6 = task_j }},
};
const int custom_flags_count = 10;

int process_format(const char *format, va_list args, char *buffer, int bufsize) {
    int pos = 0;

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            int matched = 0;

            for (int f = 0; f < custom_flags_count; f++) {
                const char *flag = custom_flags[f].flag;
                int flag_len = strlen(flag);

                if (strncmp(&format[i], flag, flag_len) == 0) {
                    char temp_result[256] = "";

                    if (custom_flags[f].arg_count == 1 && (custom_flags[f].flag == "%Zr" || custom_flags[f].flag == "%mi")) {
                        int arg = va_arg(args, int);
                        custom_flags[f].conv.converter1(arg, temp_result);
                    } else if (custom_flags[f].arg_count == 2 && (custom_flags[f].flag == "%Cv" || custom_flags[f].flag == "%CV")) {
                        int arg1 = va_arg(args, int);
                        int arg2 = va_arg(args, int);
                        custom_flags[f].conv.converter2(arg1, arg2, temp_result);
                    } else if (custom_flags[f].arg_count == 2 && (custom_flags[f].flag == "%to" || custom_flags[f].flag == "%TO")) {
                        char* arg1 = va_arg(args, char*);
                        int arg2 = va_arg(args, int);
                        custom_flags[f].conv.converter3(arg1, arg2, temp_result);
                    } else if (custom_flags[f].arg_count == 1 && (custom_flags[f].flag == "%Ro" || custom_flags[f].flag == "%mu")) {
                        unsigned int arg = va_arg(args, unsigned int);
                        custom_flags[f].conv.converter4(arg, temp_result);
                    } else if (custom_flags[f].flag == "%md") {
                        double arg = va_arg(args, double);
                        custom_flags[f].conv.converter5(arg, temp_result);
                    } else if (custom_flags[f].arg_count == 1 && custom_flags[f].flag == "%mf") {
                        double arg_t = va_arg(args, double);
                        float arg = (float) arg_t;
                        custom_flags[f].conv.converter6(arg, temp_result);
                    }

                    int len = strlen(temp_result);
                    if (pos + len >= bufsize) return -1;
                    strcpy(&buffer[pos], temp_result);
                    pos += len;

                    i += flag_len - 1;
                    matched = 1;
                    break;
                }
            }

            if (!matched) {
                char specifier[10] = "%";
                int j = 1;

                while (format[i + j] && !isalpha(format[i + j])) {
                    specifier[j] = format[i + j];
                    j++;
                }
                if (format[i + j]) {
                    specifier[j] = format[i + j];
                    j++;
                }
                specifier[j] = '\0';

                char temp[256];
                if (strcmp(specifier, "%d") == 0 || strcmp(specifier, "%i") == 0) {
                    int arg = va_arg(args, int);
                    snprintf(temp, sizeof(temp), specifier, arg);
                } else if (strcmp(specifier, "%u") == 0) {
                    unsigned int arg = va_arg(args, unsigned int);
                    snprintf(temp, sizeof(temp), specifier, arg);
                } else if (strcmp(specifier, "%s") == 0) {
                    char* arg = va_arg(args, char*);
                    snprintf(temp, sizeof(temp), specifier, arg);
                } else if (strcmp(specifier, "%c") == 0) {
                    int arg_t = va_arg(args, int);
                    char arg = (char) arg_t;
                    snprintf(temp, sizeof(temp), specifier, arg);
                } else if (strcmp(specifier, "%f") == 0 || strcmp(specifier, "%e") == 0) {
                    double arg = va_arg(args, double);
                    snprintf(temp, sizeof(temp), specifier, arg);
                } else {
                    strcpy(temp, specifier);
                }

                int len = strlen(temp);
                if (pos + len >= bufsize) return -1;
                strcpy(&buffer[pos], temp);
                pos += len;

                i += j - 1;
            }
        } else {
            if (pos >= bufsize) return -1;
            buffer[pos++] = format[i];
        }
    }

    if (pos < bufsize) buffer[pos] = '\0';
    return pos;
}


int overfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[4096];
    int result = process_format(format, args, buffer, sizeof(buffer));

    va_end(args);

    if (result != -1) {
        fputs(buffer, stream);
    }

    return result;
}

int oversprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[4096];
    int result = process_format(format, args, buffer, sizeof(buffer));

    va_end(args);

    if (result != -1) {
        fputs(buffer, stdout);
    }

    return result;
}

int main() {
    printf("\n--- overfprintf ---\n");
    overfprintf(stdout, "Number %d in Roman numerals: %Ro\n", 45, 45);
    overfprintf(stdout, "Number %u in Zeckendorf representation: %Zr\n", 431, 431);
    overfprintf(stdout, "Number %d in base %d: %Cv\n", 67, 14, 67, 14);
    overfprintf(stdout, "Number %d in base %d: %CV\n", 67, 14, 67, 14);
    overfprintf(stdout, "Number %to - its %s in base %d\n", "3a", 12, "3a", 12);
    overfprintf(stdout, "Number %TO - its %s in base %d\n", "3A", 12, "3A", 12);
    overfprintf(stdout, "Int number %d in bytes: %mi\n", 26, 26);
    overfprintf(stdout, "Unsigned int number %ud in bytes: %mu\n", 32, 32);
    overfprintf(stdout, "Double number %f in bytes: %md\n", 5.22, 5.22);
    overfprintf(stdout, "Float number %f in bytes: %mf\n", 6.00001, 6.00001);

    printf("\n--- oversprintf ---\n");
    oversprintf("Number %d in Roman numerals: %Ro\n", 45, 45);
    oversprintf("Number %u in Zeckendorf representation: %Zr\n", 100, 100);
    oversprintf("Number %d in base %d: %Cv\n", 67, 14, 67, 14);
    oversprintf("Number %d in base %d: %CV\n", 67, 14, 67, 14);
    oversprintf("Number %to - its %s in base %d\n", "3a", 12, "3a", 12);
    oversprintf("Number %TO - its %s in base %d\n", "3A", 12, "3A", 12);
    oversprintf("Int number %d in bytes: %mi\n", 26, 26);
    oversprintf("Unsigned int number %ud in bytes: %mu\n", 32, 32);
    oversprintf("Double number %f in bytes: %md\n", 5.22, 5.22);
    oversprintf("Float number %f in bytes: %mf\n", 6.00001, 6.00001);
}