#include "../include/switchSystem.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int digit_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        return 10 + (c - 'A');
    } else if (c >= 'a' && c <= 'z') {
        return 10 + (c - 'a');
    }
    return -1;
}

void switchSystem(FILE *inputFile, FILE *outputFile) {
    char c;
    int i = 0;
    int size = 20;
    char *number = (char *)malloc(size * sizeof(char));
    int is_negative = 0;
    
    while ((c = fgetc(inputFile)) != EOF) {
        if (i == 0 && (c == ' ' || c == '\t' || c == '\n')) {
            continue;
        }
        
        if ((c == ' ' || c == '\t' || c == '\n')) {
            if (i != 0) {
                number[i] = '\0'; 

                char *cleaned = number;
                is_negative = 0;
                

                if (*cleaned == '-') {
                    is_negative = 1;
                    cleaned++;
                }
                
                while (*cleaned == '0' && *(cleaned + 1) != '\0') {
                    cleaned++;
                }
                
                if (*cleaned == '\0') {
                    cleaned = "0";
                    is_negative = 0;
                }
                
                int max_digit = 0;
                char *ptr = cleaned;
                while (*ptr) {
                    int val = digit_value(*ptr);
                    if (val > max_digit) {
                        max_digit = val;
                    }
                    ptr++;
                }
                
                int base = max_digit;

                if (base < 2){
                    base = 2;
                }else{
                    base++;
                }
                
                int decimal_val = 0;
                ptr = cleaned;
                while (*ptr) {
                    int val = digit_value(*ptr);
                    decimal_val = decimal_val * base + val;
                    ptr++;
                }
                
                if (is_negative) {
                    decimal_val = -decimal_val;
                }
                
                if (is_negative && strcmp(cleaned, "0") != 0) {
                    fprintf(outputFile, "-%s %d %d\n", cleaned, base, decimal_val);
                } else {
                    fprintf(outputFile, "%s %d %d\n", cleaned, base, decimal_val);
                }
                
                i = 0;
                is_negative = 0;
            }
        } else {
            if (i >= size - 1) {
                size *= 2;
                number = (char *)realloc(number, size);
            }
            
            number[i] = toupper(c);
            i++;
        }
    }
    
    free(number);
}