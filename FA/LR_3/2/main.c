#include <stdio.h>
#include "vector.h"

// Определяем тип для нашего примера
typedef int VECTOR_TYPE;

// Функции для работы с int
int copy_int(int value) {
    return value; // Простое копирование для int
}

void delete_int(int value) {
    // Для int не нужно специального удаления
    (void)value;
}

// Определяем тип вектора для int
DEFINE_VECTOR_TYPE(int, IntVector)
// Реализуем функции для IntVector
IMPLEMENT_VECTOR_FUNCTIONS(IntVector, int)

int main() {
    // Создаем вектор
    IntVector vec = CREATE_VECTOR(IntVector, 5, copy_int, delete_int);
    
    // Добавляем элементы
    for (int i = 0; i < 10; i++) {
        PUSH_BACK_VECTOR(IntVector, &vec, i * 10);
    }
    
    // Выводим элементы
    printf("Вектор после добавления элементов:\n");
    for (size_t i = 0; i < vec.size; i++) {
        int value = GET_AT_VECTOR(IntVector, &vec, i);
        printf("%d ", value);
    }
    printf("\n");
    
    // Удаляем элемент по индексу 3
    DELETE_AT_VECTOR(IntVector, &vec, 3);
    
    printf("Вектор после удаления элемента с индексом 3:\n");
    for (size_t i = 0; i < vec.size; i++) {
        int value = GET_AT_VECTOR(IntVector, &vec, i);
        printf("%d ", value);
    }
    printf("\n");
    
    // Создаем копию вектора
    IntVector *vec_copy = COPY_VECTOR_NEW(IntVector, &vec);
    
    printf("Копия вектора:\n");
    for (size_t i = 0; i < vec_copy->size; i++) {
        int value = GET_AT_VECTOR(IntVector, vec_copy, i);
        printf("%d ", value);
    }
    printf("\n");
    
    // Проверяем сравнение
    printf("Векторы равны: %d\n", IS_EQUAL_VECTOR(IntVector, &vec, vec_copy));
    
    // Очищаем память
    DELETE_VECTOR(IntVector, vec_copy);
    ERASE_VECTOR(IntVector, &vec);
    
    return 0;
}