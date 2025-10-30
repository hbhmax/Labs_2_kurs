#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

char* intToRoman(int num) {
    const char* roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char* result = malloc(64 * sizeof(char));
    if (!result) return NULL;
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
    unsigned int fib[45];
    fib[0] = 1; fib[1] = 2;
    for (int i = 2; i < 45; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    char* result = malloc(64);
    if (!result) return NULL;
    result[0] = '\0';
    
    int found = 0;
    int pos = 0;

    for (int i = 44; i >= 0; i--) {
        if (num >= fib[i]) {
            num -= fib[i];
            result[pos++] = '1';
            found = 1;
            
            if (i > 0) i--;
        }
        else if (found) {
            result[pos++] = '0';
        }
    }
    
    if (!found) {
        result[pos++] = '0';
    }
    
    result[pos] = '\0';
    return result;
}

char* convertBase(int num, int base, int upper) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    char* result = malloc(64 * sizeof(char));
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    int sign = 1; 
    if (num < 0) {
        sign = -1;
    }

    int n = sign * num;

    do {
        int rem = n % base;
        char c;
        if (rem < 10) {
            c = '0' + rem;
        } else {
            if (upper) {
                c = 'A' + rem - 10;
            } else {
                'a' + rem - 10;
            } 
        }
        strcat(result, &c);
        n /= base;
    } while (n > 0);

    if (sign == -1) {
        strcat(result, "-");
    }

    int len = strlen(result);
    for (int i = 0; i < len / 2; i++) {
        char t = result[i];
        result[i] = result[len - i - 1];
        result[len - i - 1] = t;
    }
    return result;
}

int stringToBase(const char* str, int base) {
    if (base < 2 || base > 36 || !str) {
        return -1;
    }
    int sign = 1, i = 0;
    if (str[0] == '-') { 
        sign = -1; i++;
    }

    long long result = 0;
    for (; str[i]; i++) {
        int digit;
        if (isdigit(str[i])) {
            digit = str[i] - '0';
        } else {
            if (isupper(str[i])) {
                digit = str[i] - 'A' + 10;
            } else {
                digit = str[i] - 'a' + 10;
            }
        }
        
        if (digit >= base) {
            return -1;
        }
        result = result * base + digit;
    }
    return sign * (int)result;
}

char* memoryDump(const void* ptr, size_t size) {
    char* result = malloc(size * 9 + 1);
    if (!result) return NULL;
    result[0] = '\0';

    const unsigned char* bytes = (const unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) {
        for (int j = 7; j >= 0; j--) {
            char bit = (bytes[i] & (1 << j)) ? '1' : '0';
            strncat(result, &bit, 1);
        }
        if (i < size - 1) strncat(result, " ", 1);
    }
    return result;
}

int processSpecifier(char spec, char type, va_list args, char* buf, int bufSize) {
    switch (spec) {
        case 'R': {
            int num = va_arg(args, int);
            char* roman = intToRoman(num);
            if (!roman) return 0;
            snprintf(buf, bufSize, "%s", roman);
            free(roman);
            return 1;
        }
        case 'Z': {
            unsigned int num = va_arg(args, unsigned int);
            char* zeck = zeckendorf(num);
            if (!zeck) return 0;
            snprintf(buf, bufSize, "%s", zeck);
            free(zeck);
            return 1;
        }
        case 'C': {
            int num = va_arg(args, int);
            int base = va_arg(args, int);
            char* conv = convertBase(num, base, (type == 'V'));
            if (!conv) return 0;
            snprintf(buf, bufSize, "%s", conv);
            free(conv);
            return 1;
        }
        case 't':
        case 'T': {
            const char* str = va_arg(args, const char*);
            int base = va_arg(args, int);
            int val = stringToBase(str, base);
            snprintf(buf, bufSize, "%d", val);
            return 1;
        }
        case 'm': {
            switch (type) {
                case 'i': {
                    int val = va_arg(args, int);
                    char* dump = memoryDump(&val, sizeof(val));
                    if (!dump) return 0;
                    snprintf(buf, bufSize, "%s", dump);
                    free(dump);
                    return 1;
                }
                case 'u': {
                    unsigned int val = va_arg(args, unsigned int);
                    char* dump = memoryDump(&val, sizeof(val));
                    if (!dump) return 0;
                    snprintf(buf, bufSize, "%s", dump);
                    free(dump);
                    return 1;
                }
                case 'd': {
                    double val = va_arg(args, double);
                    char* dump = memoryDump(&val, sizeof(val));
                    if (!dump) return 0;
                    snprintf(buf, bufSize, "%s", dump);
                    free(dump);
                    return 1;
                }
                case 'f': {
                    float val = (float)va_arg(args, double);
                    char* dump = memoryDump(&val, sizeof(val));
                    if (!dump) return 0;
                    snprintf(buf, bufSize, "%s", dump);
                    free(dump);
                    return 1;
                }
                default:
                    return 0;
            }
        }
        default:
            return 0;
    }
    return 0;
}

int overfprintf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);

    char output[4096] = {0};
    char temp[256];
    const char* p = format;
    char* out_ptr = output;

    while (*p) {
        if (*p != '%') {
            *out_ptr++ = *p++;
            continue;
        }

        p++;
        if (!*p) break;

        char spec = *p++;
        if (!*p) break;
        char type = *p++;

        if (processSpecifier(spec, type, args, temp, sizeof(temp))) {
            int len = strlen(temp);
            if (out_ptr + len >= output + sizeof(output)) {
                va_end(args);
                return -1;
            }
            strcpy(out_ptr, temp);
            out_ptr += len;
        } else {
            *(out_ptr++) = '%';
            *(out_ptr++) = spec;
            *(out_ptr++) = type;
        }
    }

    *out_ptr = '\0';
    int result = fprintf(stream, "%s", output);
    va_end(args);
    return result;
}

int oversprintf(char* str, const char* format, ...) {
    va_list args;
    va_start(args, format);

    char output[4096] = {0};
    char temp[256];
    const char* p = format;
    char* out_ptr = output;

    while (*p) {
        if (*p != '%') {
            *out_ptr++ = *p++;
            continue;
        }

        p++;  
        if (!*p) break;
        char spec = *p++;
        if (!*p) break;
        char type = *p++;

        if (processSpecifier(spec, type, args, temp, sizeof(temp))) {
            int len = strlen(temp);
            if (out_ptr + len >= output + sizeof(output)) {
                va_end(args);
                return -1;
            }
            strcpy(out_ptr, temp);
            out_ptr += len;
        } else {
            *(out_ptr++) = '%';
            *(out_ptr++) = spec;
            *(out_ptr++) = type;
        }
    }

    *out_ptr = '\0';
    strcpy(str, output);
    va_end(args);
    return strlen(str);
}

int main() {
    printf("=== overfprintf demo ===\n");

    overfprintf(stdout, "Roman: %Ro\n", 2023);
    overfprintf(stdout, "Zeckendorf: %Zr\n", 123);
    overfprintf(stdout, "Base (lower): %Cv\n", 255, 16);
    overfprintf(stdout, "Base (upper): %CV\n", 255, 16);
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

    oversprintf(buffer, "Base: %Cv", 255, 2);
    printf("%s\n", buffer);

    oversprintf(buffer, "String to int: %to", "1101", 2);
    printf("%s\n", buffer);

    oversprintf(buffer, "Memory dump: %mi", -12345);
    printf("%s\n", buffer);

    return 0;
}
