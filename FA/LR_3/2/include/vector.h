#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

// Макрос для определения типа вектора
#define DEFINE_VECTOR_TYPE(T, TypeName) \
    typedef struct { \
        T *data; \
        size_t size; \
        size_t capacity; \
        T (*CopyFunc)(T); \
        void (*DeleteFunc)(T); \
    } TypeName; \
    \
    TypeName create_##TypeName(size_t initial_capacity, T (*CopyFunc)(T), void (*DeleteFunc)(T)); \
    void erase_##TypeName(TypeName *v); \
    int is_equal_##TypeName(const TypeName *v1, const TypeName *v2); \
    void copy_##TypeName(TypeName *dest, const TypeName *src); \
    TypeName *copy_##TypeName##_new(const TypeName *src); \
    void push_back_##TypeName(TypeName *v, T value); \
    void delete_at_##TypeName(TypeName *v, size_t index); \
    T get_at_##TypeName(const TypeName *v, size_t index); \
    void delete_##TypeName(TypeName *v);

// Макросы для работы с вектором (используются после DEFINE_VECTOR_TYPE)
#define CREATE_VECTOR(TypeName, capacity, copy_func, delete_func) \
    create_##TypeName(capacity, copy_func, delete_func)

#define ERASE_VECTOR(TypeName, v) erase_##TypeName(v)

#define IS_EQUAL_VECTOR(TypeName, v1, v2) is_equal_##TypeName(v1, v2)

#define COPY_VECTOR(TypeName, dest, src) copy_##TypeName(dest, src)

#define COPY_VECTOR_NEW(TypeName, src) copy_##TypeName##_new(src)

#define PUSH_BACK_VECTOR(TypeName, v, value) push_back_##TypeName(v, value)

#define DELETE_AT_VECTOR(TypeName, v, index) delete_at_##TypeName(v, index)

#define GET_AT_VECTOR(TypeName, v, index) get_at_##TypeName(v, index)

#define DELETE_VECTOR(TypeName, v) delete_##TypeName(v)

#endif