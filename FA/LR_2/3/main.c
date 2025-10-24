#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

char* intToRoman(int num) {
    const char* roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    
    char* result = malloc(20 * sizeof(char));
    result[0] = '\0';
    
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            strcat(result, roman[i]);
            num -= values[i];
        }
    }
    return result;
}

char* zeckendorf(unsigned int num) {
    unsigned int fib[90];
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i < 90; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    char* result = malloc(100 * sizeof(char));
    result[0] = '\0';
    
    for (int i = 89; i >= 0; i--) {
        if (num >= fib[i]) {
            num -= fib[i];
            strcat(result, "1");
        } else {
            strcat(result, "0");
        }
    }
    strcat(result, "1");
    return result;
}

char* convertBase(int num, int base) {
    if (base < 2 || base > 36) base = 10;
    
    char* result = malloc(100 * sizeof(char));
    result[0] = '\0';
    
    int sign = (num < 0) ? -1 : 1;
    num = abs(num);
    
    do {
        int rem = num % base;
        char digit[2];
        if (rem < 10) {
            digit[0] = '0' + rem;
        } else {
            digit[0] = 'a' + rem - 10;
        }
        digit[1] = '\0';
        strcat(result, digit);
        num /= base;
    } while (num > 0);
    
    if (sign == -1) {
        strcat(result, "-");
    }
    
    int len = strlen(result);
    for (int i = 0; i < len / 2; i++) {
        char temp = result[i];
        result[i] = result[len - i - 1];
        result[len - i - 1] = temp;
    }
    return result;
}

int stringToBase(const char* str, int base) {
    if (base < 2 || base > 36) base = 10;
    
    int result = 0;
    int sign = 1;
    
    if (*str == '-') {
        sign = -1;
        str++;
    }
    
    while (*str) {
        int digit = isdigit(*str) ? *str - '0' : tolower(*str) - 'a' + 10;
        if (digit >= base) return -1;
        result = result * base + digit;
        str++;
    }
    return sign * result;
}

char* memoryDump(const void* ptr, size_t size) {
    char* result = malloc(size * 9);
    result[0] = '\0';
    
    const unsigned char* bytes = (const unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) {
        for (int j = 7; j >= 0; j--) {
            strcat(result, (bytes[i] & (1 << j)) ? "1" : "0");
        }
        if (i < size - 1) {
            strcat(result, " ");
        }
    }
    return result;
}

void processSpecifier(char spec, va_list args, char** output, int* length) {
    char buffer[256];
    char* temp;
    
    switch (spec) {
        case 'R':
            if (*(*output - 1) == 'o') {
                int value = va_arg(args, int);
                temp = intToRoman(value);
                strcpy(buffer, temp);
                free(temp);
                *length = strlen(buffer);
                strcat(*output, buffer);
                *output += *length;
            }
            break;
            
        case 'Z':
            if (*(*output - 1) == 'r') {
                unsigned int value = va_arg(args, unsigned int);
                temp = zeckendorf(value);
                strcpy(buffer, temp);
                free(temp);
                *length = strlen(buffer);
                strcat(*output, buffer);
                *output += *length;
            }
            break;
            
        case 'C':
            if (*(*output - 1) == 'v' || *(*output - 1) == 'V') {
                int value = va_arg(args, int);
                int base = va_arg(args, int);
                temp = convertBase(value, base);
                if (*(*output - 1) == 'V') {
                    for (char* p = temp; *p; p++) {
                        *p = toupper(*p);
                    }
                }
                strcpy(buffer, temp);
                free(temp);
                *length = strlen(buffer);
                strcat(*output, buffer);
                *output += *length;
            }
            break;
            
        case 't':
            if (*(*output - 1) == 'o') {
                char* str = va_arg(args, char*);
                int base = va_arg(args, int);
                int value = stringToBase(str, base);
                sprintf(buffer, "%d", value);
                *length = strlen(buffer);
                strcat(*output, buffer);
                *output += *length;
            }
            break;
            
        case 'T':
            if (*(*output - 1) == 'O') {
                char* str = va_arg(args, char*);
                int base = va_arg(args, int);
                int value = stringToBase(str, base);
                sprintf(buffer, "%d", value);
                *length = strlen(buffer);
                strcat(*output, buffer);
                *output += *length;
            }
            break;
            
        case 'm':
            {
                char type = *(*output - 1);
                switch (type) {
                    case 'i': {
                        int value = va_arg(args, int);
                        temp = memoryDump(&value, sizeof(value));
                        break;
                    }
                    case 'u': {
                        unsigned int value = va_arg(args, unsigned int);
                        temp = memoryDump(&value, sizeof(value));
                        break;
                    }
                    case 'd': {
                        double value = va_arg(args, double);
                        temp = memoryDump(&value, sizeof(value));
                        break;
                    }
                    case 'f': {
                        float value = (float)va_arg(args, double);
                        temp = memoryDump(&value, sizeof(value));
                        break;
                    }
                    default:
                        temp = malloc(1);
                        temp[0] = '\0';
                        break;
                }
                strcpy(buffer, temp);
                free(temp);
                *length = strlen(buffer);
                strcat(*output, buffer);
                *output += *length;
            }
            break;
    }
}

int overfprintf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    char* output = buffer;
    const char* p = format;
    
    while (*p) {
        if (*p != '%') {
            *output++ = *p++;
            continue;
        }
        
        p++;
        if (*p == '\0') break;
        
        if (strchr("RZCTm", *p)) {
            char spec = *p;
            p++;
            if (*p == '\0') break;
            
            *output++ = '%';
            *output++ = spec;
            *output++ = *p;
            *output = '\0';
            
            int length;
            processSpecifier(spec, args, &output, &length);
            p++;
        } else {
            *output++ = '%';
            *output++ = *p++;
        }
    }
    
    *output = '\0';
    int result = fprintf(stream, "%s", buffer);
    va_end(args);
    return result;
}

int oversprintf(char* str, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    char* output = str;
    const char* p = format;
    
    while (*p) {
        if (*p != '%') {
            *output++ = *p++;
            continue;
        }
        
        p++;
        if (*p == '\0') break;
        
        if (strchr("RZCTm", *p)) {
            char spec = *p;
            p++;
            if (*p == '\0') break;
            
            *output++ = '%';
            *output++ = spec;
            *output++ = *p;
            *output = '\0';
            
            int length;
            processSpecifier(spec, args, &output, &length);
            p++;
        } else {
            *output++ = '%';
            *output++ = *p++;
        }
    }
    
    *output = '\0';
    va_end(args);
    return strlen(str);
}

int main() {
    printf("=== overfprintf demo ===\n");
    overfprintf(stdout, "Roman: %Ro\n", 2023);
    overfprintf(stdout, "Zeckendorf: %Zr\n", 123);
    overfprintf(stdout, "Base conv (lower): %Cv\n", 255, 16);
    overfprintf(stdout, "Base conv (upper): %CV\n", 255, 16);
    overfprintf(stdout, "String to int (lower): %to\n", "ff", 16);
    overfprintf(stdout, "String to int (upper): %TO\n", "FF", 16);
    
    int si = -123456;
    unsigned int ui = 123456;
    double d = 3.14159;
    float f = 2.71828f;
    
    overfprintf(stdout, "Memory dump int: %mi\n", si);
    overfprintf(stdout, "Memory dump uint: %mu\n", ui);
    overfprintf(stdout, "Memory dump double: %md\n", d);
    overfprintf(stdout, "Memory dump float: %mf\n", f);
    
    printf("\n=== oversprintf demo ===\n");
    char buffer[1024];
    
    oversprintf(buffer, "Roman: %Ro", 1984);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Zeckendorf: %Zr", 456);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Base conv: %Cv", 255, 2);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "String to int: %to", "1101", 2);
    printf("%s\n", buffer);
    
    oversprintf(buffer, "Memory dump: %mi", -12345);
    printf("%s\n", buffer);
    
    return 0;
}