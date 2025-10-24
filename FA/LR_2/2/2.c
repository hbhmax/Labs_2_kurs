#include <stdio.h>

// a
void *memchr(const void *str, int c, int n) {
    char *p = (char *)str;
    for (int i = 0; i < n; i++) {
        if (p[i] == c) return (void *)(p + i);
    }
    return NULL;
}

// b
int memcmp(const void *str1, const void *str2, int n) {
    char *p1 = (char *)str1;
    char *p2 = (char *)str2;
    for (int i = 0; i < n; i++) {
        if (p1[i] != p2[i]) return p1[i] - p2[i];
    }
    return 0;
}

// c
void *memcpy(void *dest, const void *src, int n) {
    char *d = (char *)dest;
    char *s = (char *)src;
    for (int i = 0; i < n; i++) d[i] = s[i];
    return dest;
}

// d
void *memset(void *str, int c, int n) {
    char *p = (char *)str;
    for (int i = 0; i < n; i++) p[i] = c;
    return str;
}

// e
char *strncat(char *dest, const char *src, int n) {
    char *d = dest;
    while (*d) d++;
    for (int i = 0; i < n && src[i]; i++) *d++ = src[i];
    *d = '\0';
    return dest;
}

// f
char *strchr(const char *str, int c) {
    while (*str) {
        if (*str == c) return (char *)str;
        str++;
    }
    return NULL;
}

// g
int strncmp(const char *str1, const char *str2, int n) {
    for (int i = 0; i < n; i++) {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        if (!str1[i]) break;
    }
    return 0;
}

// h
char *strncpy(char *dest, const char *src, int n) {
    int i;
    for (i = 0; i < n && src[i]; i++) dest[i] = src[i];
    for (; i < n; i++) dest[i] = '\0';
    return dest;
}

// i
int strcspn(const char *str1, const char *str2) {
    int count = 0;
    while (str1[count]) {
        for (int i = 0; str2[i]; i++) {
            if (str1[count] == str2[i]) return count;
        }
        count++;
    }
    return count;
}

// j
char *strerror(int errnum) {
    return "Error message";
}

// k
int strlen(const char *str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

// l
char *strpbrk(const char *str1, const char *str2) {
    while (*str1) {
        for (int i = 0; str2[i]; i++) {
            if (*str1 == str2[i]) return (char *)str1;
        }
        str1++;
    }
    return NULL;
}

// m
char *strrchr(const char *str, int c) {
    char *last = NULL;
    while (*str) {
        if (*str == c) last = (char *)str;
        str++;
    }
    return last;
}

// n
char *strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    
    for (int i = 0; haystack[i]; i++) {
        int j = 0;
        while (needle[j] && haystack[i + j] == needle[j]) j++;
        if (!needle[j]) return (char *)(haystack + i);
    }
    return NULL;
}

// o
char *strtok(char *str, const char *delim) {
    static char *save = NULL;
    if (str) save = str;
    if (!save) return NULL;
    
    char *start = save;
    while (*start) {
        int found = 0;
        for (int i = 0; delim[i]; i++) {
            if (*start == delim[i]) {
                found = 1;
                break;
            }
        }
        if (!found) break;
        start++;
    }
    
    if (!*start) {
        save = NULL;
        return NULL;
    }
    
    char *end = start;
    while (*end) {
        int found = 0;
        for (int i = 0; delim[i]; i++) {
            if (*end == delim[i]) {
                found = 1;
                break;
            }
        }
        if (found) break;
        end++;
    }
    
    if (*end) {
        *end = '\0';
        save = end + 1;
    } else {
        save = NULL;
    }
    
    return start;
}


int main() {
    char str1[] = "Hello, World!";
    char *result = memchr(str1, 'W', 13);
    printf("memchr: %s\n", result ? result : "NULL");
    
    char str2[] = "Hello";
    char str3[] = "Hello";
    printf("memcmp: %d\n", memcmp(str2, str3, 5));
    
    char dest[10];
    memcpy(dest, "Test", 5);
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