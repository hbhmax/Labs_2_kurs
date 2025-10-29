
#include <stdio.h>
#include <stdlib.h>

// a
void *memchr(const void *str, int c, size_t n) {
    const unsigned char *p = (const unsigned char *)str;
    unsigned char uc = (unsigned char)c;
    for (size_t i = 0; i < n; i++) {
        if (p[i] == uc) return (void *)(p + i);
    }
    return NULL;
}

// b
int memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) return 0;
    }
    return 1;
}

// c
void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

// d
void *memset(void *str, int c, size_t n) {
    unsigned char *p = (unsigned char *)str;
    unsigned char uc = (unsigned char)c;
    for (size_t i = 0; i < n; i++) {
        p[i] = uc;
    }
    return str;
}

// e
char *strncat(char *dest, const char *src, size_t n) {
    char *d = dest;
    while (*d) {d++;}
    for (size_t i = 0; i < n && src[i]; i++) {
        *d++ = src[i];
    }
    *d = '\0';
    return dest;
}

// f
char *strchr(const char *str, int c) {
    unsigned char uc = (unsigned char)c;
    while (*str) {
        if ((unsigned char)*str == uc) {
            return (char *)str;
        }
        str++;
    }
    if (uc == '\0') return (char *)str;
    return NULL;
}

// g
int strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (!str1[i] || !str2[i] || str1[i] != str2[i]) {
            return 0;
        } 
    }
    return 1;
}

// h
char *strncpy(char *dest, const char *src, size_t n) {
    for (size_t i = 0; i < n && src[i]; i++) {
        dest[i] = src[i];
    }
    for (size_t i = 0; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

// i
size_t strcspn(const char *str1, const char *str2) {
    size_t count = 0;
    while (str1[count]) {
        for (size_t i = 0; str2[i]; i++) {
            if (str1[count] == str2[i]) {
                return count;
            }
        }
        count++;
    }
    return count;
}

// j
char *strerror(int errnum) {
    #ifdef __APPLE__
        static const char *mac_errors[] = {
            [0]  = "Undefined error: 0",
            [1]  = "Operation not permitted",
            [2]  = "No such file or directory",
            [3]  = "No such process",
            [4]  = "Interrupted system call",
            [5]  = "Input/output error",
            [6]  = "Device not configured",
            [7]  = "Argument list too long",
            [8]  = "Exec format error",
            [9]  = "Bad file descriptor",
            [10] = "No child processes",
        };

        if (errnum >= 0 && errnum <= 10) {
            return (char*)mac_errors[errnum];
        } else {
            return "Unknown error";
        }

    #elif __linux__
        static const char *linux_errors[] = {
            [0]  = "Success",
            [1]  = "Operation not permitted",
            [2]  = "No such file or directory",
            [3]  = "No such process",
            [4]  = "Interrupted system call",
            [5]  = "Input/output error",
            [6]  = "No such device or address",
            [7]  = "Argument list too long",
            [8]  = "Exec format error",
            [9]  = "Bad file descriptor",
            [10] = "No child processes",
        };

        if (errnum >= 0 && errnum <= 10) {
            return (char*)linux_errors[errnum];
        } else {
            return "Unknown error";
        }

    #else
        return "Unsupported OS or platform";
    #endif
}


// k
size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len]) {len++;}
    return len;
}

// l
char *strpbrk(const char *str1, const char *str2) {
    while (*str1) {
        for (size_t i = 0; str2[i]; i++) {
            if (*str1 == str2[i]) {
                return (char *)str1;
            }
        }
        str1++;
    }
    return NULL;
}

// m
char *strrchr(const char *str, int c) {
    char *last = NULL;
    unsigned char uc = (unsigned char)c;
    while (*str) {
        if ((unsigned char)*str == uc) {
            last = (char *)str;
        }
        str++;
    }
    if (uc == '\0') {
        last = (char *)str;
    }
    return last;
}

// n
char *strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack;
    }

    for (size_t i = 0; haystack[i]; i++) {
        size_t j;
        for (j = 0; needle[j] && haystack[i + j] == needle[j]; j++);
        if (!needle[j]) {
            return (char *)(haystack + i);
        }
    }
    return NULL;
}

// o
char *strtok(char *str, const char *delim) {
    static char *save = NULL;
    if (str) {
        save = str;
    }
    if (!save) {
        return NULL;
    }

    while (*save) {
        int found = 0;
        for (size_t i = 0; delim[i]; i++) {
            if (*save == delim[i]) {
                found = 1;
                break;
            }
        }
        if (!found) break;
        save++;
    }

    if (!*save) {
        save = NULL;
        return NULL;
    }

    char *start = save;
    while (*save) {
        int found = 0;
        for (size_t i = 0; delim[i]; i++) {
            if (*save == delim[i]) {
                found = 1;
                break;
            }
        }
        if (found) break;
        save++;
    }

    if (*save) {
        *save = '\0';
        save++;
    } else {
        save = NULL;
    }

    return start;
}

int main() {
    char str1[] = "Hello, World!";
    printf("memchr: %s\n", (char *)memchr(str1, 'W', 13));

    char str2[] = "Hello";
    char str3[] = "Hellp";
    printf("memcmp: %d\n", memcmp(str2, str3, 4));

    char dest[10];
    memcpy(dest, "Test", 3);
    printf("memcpy: %s\n", dest);

    char buf[10];
    memset(buf, 'A', 5);
    buf[5] = '\0';
    printf("memset: %s\n", buf);

    char dest2[20] = "Hello";
    strncat(dest2, " World", 6);
    printf("strncat: %s\n", dest2);
    
    printf("strchr: %s\n", strchr("Hello", 'e'));
    
    printf("strncmp: %d\n", strncmp("Hello", "Hell", 4));
    
    char dest3[10];
    strncpy(dest3, "Hello", 3);
    dest3[3] = '\0';
    printf("strncpy: %s\n", dest3);
    
    printf("strcspn: %zu\n", strcspn("Hello", "lo"));
    
    printf("strerror: %s\n", strerror(2));
    
    printf("strlen: %zu\n", strlen("Hello"));
    
    printf("strpbrk: %s\n", strpbrk("Hello", "lo"));
    
    printf("strrchr: %s\n", strrchr("Hello", 'l'));
    
    printf("strstr: %s\n", strstr("Hello World", "World"));
    
    char str4[] = "Hello,World,Test";
    char *token = strtok(str4, ",");
    printf("strtok: ");
    while (token != NULL) {
        printf("%s ", token);
        token = strtok(NULL, ",");
    }
    printf("\n");
    
    return 0;
}