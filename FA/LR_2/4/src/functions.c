#include "../include/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

int roman_digit_value(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

int roman_to_int(const char *s) {
    int total = 0;
    int prev_value = 0;
    
    while (*s) {
        int value = roman_digit_value(*s++);
        total += value;
        if (prev_value < value) {
            total -= 2 * prev_value;
        }
        prev_value = value;
    }
    return total;
}

unsigned int zeckendorf_to_int(const char *s) {
    if (!s || !*s) {
        return 0;
    }
    
    int len = strlen(s);
    
    if (len == 0 || s[len - 1] != '1') {
        return 0;
    }
    
    if (len == 1) {
        return 0;
    }

    unsigned int fib[MAX_FIB];
    fib[0] = 1;
    fib[1] = 2;
    
    for (int i = 2; i < MAX_FIB; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    unsigned int result = 0;

    for (int i = 0; i < len - 1; i++) {
        char c = s[i];
        
        if (c != '0' && c != '1') {
            return 0;
        }
        
        if (c == '1') {
            if (i > 0 && s[i - 1] == '1') {
                return 0; 
            }
            if (i < MAX_FIB) {
                result += fib[i];
            } else {
                return 0;
            }
        }
    }

    return result;
}

static int str_to_int_base(const char *str, int base, int uppercase) {
    if (base < 2 || base > 36) {
        base = 10;
    }
    
    int result = 0;
    int sign = 1;
    const char *p = str;
    
    while (*p && isspace(*p)) p++;
    
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }
    
    while (*p) {
        int digit;
        char c = *p;
        
        if (isdigit(c)) {
            digit = c - '0';
        } else if (isalpha(c)) {
            if (uppercase) {
                digit = toupper(c) - 'A' + 10;
            } else {
                digit = tolower(c) - 'a' + 10;
            }
        } else {
            break;
        }
        
        if (digit >= base) {
            break;
        }
        
        result = result * base + digit;
        p++;
    }
    
    return result * sign;
}

int overfscanf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int count = 0;
    const char *p = format;
    
    while (*p) {
        if (*p != '%') {
            p++;
            continue;
        }
        
        p++;
        if (*p == 'R' && *(p+1) == 'o') {
            p += 2;
            
            int c;
            while ((c = fgetc(stream)) != EOF && isspace(c));
            
            if (c == EOF) break;
            
            char roman[20] = {0};
            int i = 0;
            
            do {
                roman[i++] = c;
                if (i >= 19) break;
            } while ((c = fgetc(stream)) != EOF && roman_digit_value(c));
            
            if (c != EOF) ungetc(c, stream);
            
            int *arg = va_arg(args, int*);
            *arg = roman_to_int(roman);
            count++;
        } else if (*p == 'Z' && *(p+1) == 'r') {
            p += 2;
            
            int c;
            while ((c = fgetc(stream)) != EOF && isspace(c));
            
            if (c == EOF) break;
            
            char zek[100] = {0};
            int i = 0;
            
            while ((c == '0' || c == '1') && i < 99) {
                zek[i++] = c;
                c = fgetc(stream);
            }
            
            if (c != EOF) ungetc(c, stream);
            
            unsigned int *arg = va_arg(args, unsigned int*);
            *arg = zeckendorf_to_int(zek);
            count++;
        } else if (*p == 'C' && (*(p+1) == 'v' || *(p+1) == 'V')) {
            int uppercase = (*(p+1) == 'V');
            p += 2;
            
            int *arg = va_arg(args, int*);
            int base = va_arg(args, int);
            
            int c;
            while ((c = fgetc(stream)) != EOF && isspace(c));
            
            if (c == EOF) break;
            
            char num_str[100] = {0};
            int i = 0;
            
            if (c == '+' || c == '-') {
                num_str[i++] = c;
                c = fgetc(stream);
            }
            
            while (c != EOF && i < 99) {
                if (isdigit(c) || 
                    (uppercase && isupper(c)) || 
                    (!uppercase && islower(c))) {
                    num_str[i++] = c;
                } else {
                    ungetc(c, stream);
                    break;
                }
                c = fgetc(stream);
            }
            
            *arg = str_to_int_base(num_str, base, uppercase);
            count++;
        } else {
            char spec[3] = {'%', *p, '\0'};
            switch (*p) {
                case 'd':
                case 'i':
                    count += fscanf(stream, spec, va_arg(args, int*));
                    break;
                case 'u':
                    count += fscanf(stream, spec, va_arg(args, unsigned int*));
                    break;
                case 'c':
                    count += fscanf(stream, spec, va_arg(args, char*));
                    break;
                case 's':
                    count += fscanf(stream, spec, va_arg(args, char*));
                    break;
                case 'f':
                    count += fscanf(stream, spec, va_arg(args, double*));
                    break;
            }
            p++;
        }
    }
    
    va_end(args);
    return count;
}

int oversscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int count = 0;
    const char *p = format;
    const char *s = str;
    
    while (*p && *s) {
        if (*p != '%') {
            if (*p != *s) break;
            p++;
            s++;
            continue;
        }
        
        p++;
        if (*p == 'R' && *(p+1) == 'o') {
            p += 2;
            
            while (*s && isspace(*s)) s++;
            
            char roman[20] = {0};
            int i = 0;
            
            while (*s && roman_digit_value(*s)) {
                if (i < 19) roman[i++] = *s;
                s++;
            }
            
            int *arg = va_arg(args, int*);
            *arg = roman_to_int(roman);
            count++;
        } else if (*p == 'Z' && *(p+1) == 'r') {
            p += 2;
            
            while (*s && isspace(*s)) s++;
            
            char zek[100] = {0};
            int i = 0;
            
            while (*s && (*s == '0' || *s == '1') && i < 99) {
                zek[i++] = *s++;
            }
            
            unsigned int *arg = va_arg(args, unsigned int*);
            *arg = zeckendorf_to_int(zek);
            count++;
        } else if (*p == 'C' && (*(p+1) == 'v' || *(p+1) == 'V')) {
            int uppercase = (*(p+1) == 'V');
            p += 2;
            
            int *arg = va_arg(args, int*);
            int base = va_arg(args, int);
            
            while (*s && isspace(*s)) s++;
            
            char num_str[100] = {0};
            int i = 0;
            
            if (*s == '+' || *s == '-') {
                num_str[i++] = *s++;
            }
            
            while (*s && i < 99) {
                if (isdigit(*s) || 
                    (uppercase && isupper(*s)) || 
                    (!uppercase && islower(*s))) {
                    num_str[i++] = *s++;
                } else {
                    break;
                }
            }
            
            *arg = str_to_int_base(num_str, base, uppercase);
            count++;
        } else {
            char spec[3] = {'%', *p, '\0'};
            switch (*p) {
                case 'd':
                case 'i':
                    count += sscanf(s, spec, va_arg(args, int*));
                    while (*s && !isspace(*s)) s++;
                    break;
                case 'u':
                    count += sscanf(s, spec, va_arg(args, unsigned int*));
                    while (*s && !isspace(*s)) s++;
                    break;
                case 'f':
                    count += sscanf(s, spec, va_arg(args, double*));
                    while (*s && !isspace(*s)) s++;
                    break;
                case 'c':
                    count += sscanf(s, spec, va_arg(args, char*));
                    while (*s && !isspace(*s)) s++;
                    break;
                case 's':
                    count += sscanf(s, spec, va_arg(args, char*));
                    while (*s && !isspace(*s)) s++;
                    while (*s && isspace(*s)) s++;
                    break;
            }
            p++;
        }
    }
    
    va_end(args);
    return count;
}