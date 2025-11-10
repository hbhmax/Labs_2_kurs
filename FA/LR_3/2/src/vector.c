#include "vector.h"

// Создание нового вектора
#define IMPLEMENT_VECTOR_FUNCTIONS(TypeName, T) \
TypeName create_##TypeName(size_t initial_capacity, T (*CopyFunc)(T), void (*DeleteFunc)(T)) { \
    TypeName v; \
    v.size = 0; \
    v.capacity = initial_capacity > 0 ? initial_capacity : 1; \
    v.CopyFunc = CopyFunc; \
    v.DeleteFunc = DeleteFunc; \
    v.data = (T*)malloc(v.capacity * sizeof(T)); \
    if (!v.data) { \
        v.capacity = 0; \
    } \
    return v; \
} \
\
/* Удаление внутреннего содержимого вектора */ \
void erase_##TypeName(TypeName *v) { \
    if (v && v->data && v->DeleteFunc) { \
        for (size_t i = 0; i < v->size; i++) { \
            v->DeleteFunc(v->data[i]); \
        } \
    } \
    if (v && v->data) { \
        free(v->data); \
        v->data = NULL; \
    } \
    if (v) { \
        v->size = 0; \
        v->capacity = 0; \
    } \
} \
\
/* Сравнение двух векторов (лексикографически) */ \
int is_equal_##TypeName(const TypeName *v1, const TypeName *v2) { \
    if (v1 == v2) return 1; \
    if (!v1 || !v2) return 0; \
    if (v1->size != v2->size) return 0; \
    \
    for (size_t i = 0; i < v1->size; i++) { \
        if (v1->data[i] != v2->data[i]) { \
            return 0; \
        } \
    } \
    return 1; \
} \
\
/* Копирование содержимого одного вектора в другой (существующий) */ \
void copy_##TypeName(TypeName *dest, const TypeName *src) { \
    if (!dest || !src || !src->CopyFunc) return; \
    \
    /* Очищаем целевой вектор */ \
    erase_##TypeName(dest); \
    \
    /* Устанавливаем функции */ \
    dest->CopyFunc = src->CopyFunc; \
    dest->DeleteFunc = src->DeleteFunc; \
    \
    /* Выделяем память */ \
    dest->capacity = src->capacity; \
    dest->size = src->size; \
    dest->data = (T*)malloc(dest->capacity * sizeof(T)); \
    if (!dest->data) { \
        dest->capacity = 0; \
        dest->size = 0; \
        return; \
    } \
    \
    /* Копируем элементы */ \
    for (size_t i = 0; i < src->size; i++) { \
        dest->data[i] = src->CopyFunc(src->data[i]); \
    } \
} \
\
/* Создание нового вектора в динамической памяти и копирование содержимого */ \
TypeName *copy_##TypeName##_new(const TypeName *src) { \
    if (!src) return NULL; \
    \
    TypeName *new_vec = (TypeName*)malloc(sizeof(TypeName)); \
    if (!new_vec) return NULL; \
    \
    new_vec->data = NULL; \
    new_vec->size = 0; \
    new_vec->capacity = 0; \
    copy_##TypeName(new_vec, src); \
    return new_vec; \
} \
\
/* Добавление элемента в конец вектора */ \
void push_back_##TypeName(TypeName *v, T value) { \
    if (!v || !v->CopyFunc) return; \
    \
    /* Проверяем, нужно ли увеличить capacity */ \
    if (v->size >= v->capacity) { \
        size_t new_capacity = v->capacity == 0 ? 1 : v->capacity * 2; \
        T *new_data = (T*)realloc(v->data, new_capacity * sizeof(T)); \
        if (!new_data) return; \
        v->data = new_data; \
        v->capacity = new_capacity; \
    } \
    \
    /* Копируем и добавляем элемент */ \
    v->data[v->size] = v->CopyFunc(value); \
    v->size++; \
} \
\
/* Удаление элемента по индексу */ \
void delete_at_##TypeName(TypeName *v, size_t index) { \
    if (!v || index >= v->size || !v->DeleteFunc) return; \
    \
    /* Удаляем элемент */ \
    v->DeleteFunc(v->data[index]); \
    \
    /* Сдвигаем оставшиеся элементы */ \
    for (size_t i = index; i < v->size - 1; i++) { \
        v->data[i] = v->data[i + 1]; \
    } \
    v->size--; \
} \
\
/* Получение элемента по индексу */ \
T get_at_##TypeName(const TypeName *v, size_t index) { \
    if (!v || index >= v->size) { \
        T null_value = {0}; \
        return null_value; \
    } \
    return v->data[index]; \
} \
\
/* Освобождение памяти, занимаемой экземпляром вектора */ \
void delete_##TypeName(TypeName *v) { \
    if (!v) return; \
    erase_##TypeName(v); \
    free(v); \
}