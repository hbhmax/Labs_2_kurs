// === functions.h ===
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

// Коды ошибок
typedef enum {
    SUCCESS = 0,
    ERROR_ZECKENDORF_NEGATIVE,
    ERROR_BASE_OUT_OF_RANGE,
    ERROR_INVALID_NUMBER_FORMAT,
    ERROR_INVALID_CHARACTER,
    ERROR_EMPTY_STRING,
    ERROR_INVALID_CASE        
} ErrorCode;

// Структура для возврата результата
typedef struct {
    char result[256];
    ErrorCode error;
} ConversionResult;

// Прототипы функций
int overfprintf(FILE *stream, const char *format, ...);
int oversprintf(const char *format, ...);

// Функции-задания теперь возвращают ConversionResult
ConversionResult task_a(unsigned int num);
ConversionResult task_b(int num);
ConversionResult task_c(int num, int base);
ConversionResult task_d(int num, int base);
ConversionResult task_e(char *num, int base);
ConversionResult task_f(char *num, int base);
ConversionResult task_g(int num);
ConversionResult task_h(unsigned int num);
ConversionResult task_i(double num);
ConversionResult task_j(float num);

// Функция для получения сообщения об ошибке
const char* get_error_message(ErrorCode error);

#endif