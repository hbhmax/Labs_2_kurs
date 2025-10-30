#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

int romanToInt(const char* s) {
    int romanValues[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* romanSymbols[] = {"m", "cm", "d", "cd", "c", "xc", "l", "xl", "x", "ix", "v", "iv", "i"};
    
    int result = 0;
    const char* ptr = s;
    
    while (*ptr) {
        int found = 0;
        for (int i = 0; i < 13; i++) {
            int len = strlen(romanSymbols[i]);
            if (strncmp(ptr, romanSymbols[i], len) == 0) {
                result += romanValues[i];
                ptr += len;
                found = 1;
                break;
            }
        }
        if (!found) {
            ptr++;
        }
    }
    return result;
}

unsigned int zeckendorfToInt(const char* s) {
    unsigned int result = 0;
    unsigned int fib[45];
    fib[0] = 1;
    fib[1] = 2;
    
    for (int i = 2; i < 45; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    int len = strlen(s);
    int fib_index = 0;
    
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == '1') {
            result += fib[fib_index];
            
            fib_index += 2;
        } else {
            fib_index++;
        }
    }
    
    return result;
}

int convertBase(const char* s, int base) {
    int result = 0;
    int sign = 1;
    
    if (*s == '-') {
        sign = -1;
        s++;
    }
    
    for (; *s; s++) {
        int digit;
        if (isdigit(*s)) {
            digit = *s - '0';
        } else if (isalpha(*s)) {
            digit = tolower(*s) - 'a' + 10;
        } else {
            return 0;
        }
        
        if (digit >= base) {
            return 0;
        }
        result = result * base + digit;
    }
    return sign * result;
}

int overfscanf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = 0;
    const char* p = format;
    
    while (*p) {
        if (*p != '%') {
            p++;
            continue;
        }
        
        p++;
        if (*p == '\0') break;
        
        if (*p == 'R') {
            if (p[1] == 'o') {
                char buffer[100];
                if (fscanf(stream, "%99s", buffer) == 1) {
                    for (char* c = buffer; *c; c++) {
                        *c = tolower(*c);
                    }
                    int* ptr = va_arg(args, int*);
                    *ptr = romanToInt(buffer);
                    result++;
                }
                p += 2;
            } else {
                p++;
            }
        } else if (*p == 'Z') {
            if (p[1] == 'r') {
                char buffer[100];
                if (fscanf(stream, "%99s", buffer) == 1) {
                    unsigned int* ptr = va_arg(args, unsigned int*);
                    *ptr = zeckendorfToInt(buffer);
                    result++;
                }
                p += 2;
            } else {
                p++;
            }
        } else if (*p == 'C') {
            if (p[1] == 'v') {
                int* ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                char buffer[100];
                if (fscanf(stream, "%99s", buffer) == 1) {
                    for (char* c = buffer; *c; c++) {
                        *c = tolower(*c);
                    }
                    *ptr = convertBase(buffer, base);
                    result++;
                }
                p += 2;
            } else if (p[1] == 'V') {
                int* ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                char buffer[100];
                if (fscanf(stream, "%99s", buffer) == 1) {
                    for (char* c = buffer; *c; c++) {
                        *c = toupper(*c);
                    }
                    *ptr = convertBase(buffer, base);
                    result++;
                }
                p += 2;
            } else {
                p++;
            }
        } else {
            p++;
        }
    }
    
    va_end(args);
    return result;
}

int oversscanf(const char* str, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = 0;
    const char* str_ptr = str;
    const char* fmt_ptr = format;
    
    while (*fmt_ptr && *str_ptr) {
        if (*fmt_ptr != '%') {
            if (*fmt_ptr == *str_ptr) {
                fmt_ptr++;
                str_ptr++;
            } else {
                while (*str_ptr && isspace(*str_ptr)) str_ptr++;
                while (*fmt_ptr && isspace(*fmt_ptr)) fmt_ptr++;
            }
            continue;
        }
        
        fmt_ptr++;
        if (*fmt_ptr == '\0') break;
        
        if (*fmt_ptr == 'R') {
            if (fmt_ptr[1] == 'o') {
                char buffer[100];
                int i = 0;
                
                while (*str_ptr && isspace(*str_ptr)) str_ptr++;
                
                while (*str_ptr && !isspace(*str_ptr) && i < 99) {
                    buffer[i++] = tolower(*str_ptr++);
                }
                buffer[i] = '\0';
                
                if (i > 0) {
                    int* ptr = va_arg(args, int*);
                    *ptr = romanToInt(buffer);
                    result++;
                }
                fmt_ptr += 2;
            } else {
                fmt_ptr++;
            }
        } else if (*fmt_ptr == 'Z') {
            if (fmt_ptr[1] == 'r') {
                char buffer[100];
                int i = 0;
                
                while (*str_ptr && isspace(*str_ptr)) str_ptr++;
                
                while (*str_ptr && !isspace(*str_ptr) && i < 99) {
                    buffer[i++] = *str_ptr++;
                }
                buffer[i] = '\0';
                
                if (i > 0) {
                    unsigned int* ptr = va_arg(args, unsigned int*);
                    *ptr = zeckendorfToInt(buffer);
                    result++;
                }
                fmt_ptr += 2;
            } else {
                fmt_ptr++;
            }
        } else if (*fmt_ptr == 'C') {
            if (fmt_ptr[1] == 'v') {
                int* ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                
                char buffer[100];
                int i = 0;
                
                while (*str_ptr && isspace(*str_ptr)) str_ptr++;
                
                while (*str_ptr && !isspace(*str_ptr) && i < 99) {
                    buffer[i++] = tolower(*str_ptr++);
                }
                buffer[i] = '\0';
                
                if (i > 0) {
                    *ptr = convertBase(buffer, base);
                    result++;
                }
                fmt_ptr += 2;
            } else if (fmt_ptr[1] == 'V') {
                int* ptr = va_arg(args, int*);
                int base = va_arg(args, int);
                if (base < 2 || base > 36) base = 10;
                
                char buffer[100];
                int i = 0;
                
                while (*str_ptr && isspace(*str_ptr)) str_ptr++;
                
                while (*str_ptr && !isspace(*str_ptr) && i < 99) {
                    buffer[i++] = toupper(*str_ptr++);
                }
                buffer[i] = '\0';
                
                if (i > 0) {
                    *ptr = convertBase(buffer, base);
                    result++;
                }
                fmt_ptr += 2;
            } else {
                fmt_ptr++;
            }
        } else {
            fmt_ptr++;
        }
    }
    
    va_end(args);
    return result;
}

int main() {
    printf("=== overfscanf demo ===\n");
    
    printf("Enter a Roman numeral: ");
    int roman;
    if (overfscanf(stdin, "%Ro", &roman) == 1) {
        printf("Read Roman: %d\n", roman);
    }
    
    printf("Enter a Zeckendorf representation: ");
    unsigned int zeck;
    if (overfscanf(stdin, "%Zr", &zeck) == 1) {
        printf("Read Zeckendorf: %u\n", zeck);
    }
    
    printf("Enter a base-16 number (lowercase): ");
    int base16_lower;
    if (overfscanf(stdin, "%Cv", &base16_lower, 16) == 1) {
        printf("Read base-16 (lower): %d\n", base16_lower);
    }
    
    printf("Enter a base-16 number (uppercase): ");
    int base16_upper;
    if (overfscanf(stdin, "%CV", &base16_upper, 16) == 1) {
        printf("Read base-16 (upper): %d\n", base16_upper);
    }
    
    printf("\n=== oversscanf demo ===\n");
    
    const char* test_str1 = "xiv 1001011 ff FF";
    int r1;
    unsigned int z1;
    int b1, b2;
    
    int count = oversscanf(test_str1, "%Ro %Zr %Cv %CV", &r1, &z1, &b1, 16, &b2, 16);
    printf("Read from '%s':\n", test_str1);
    printf("Roman: %d, Zeckendorf: %u, Base16(lower): %d, Base16(upper): %d\n", r1, z1, b1, b2);
    printf("Total conversions: %d\n", count);
    
    const char* test_str2 = "cmxlix 1010101 1a 1A";
    int r2;
    unsigned int z2;
    int b3, b4;
    
    count = oversscanf(test_str2, "%Ro %Zr %Cv %CV", &r2, &z2, &b3, 16, &b4, 16);
    printf("\nRead from '%s':\n", test_str2);
    printf("Roman: %d, Zeckendorf: %u, Base16(lower): %d, Base16(upper): %d\n", r2, z2, b3, b4);
    printf("Total conversions: %d\n", count);
    
    return 0;
}