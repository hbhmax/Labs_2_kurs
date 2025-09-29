#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

// Функция проверки гласных (английские и русские)
int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
            c == 'а' || c == 'е' || c == 'и' || c == 'о' || c == 'у' || 
            c == 'ы' || c == 'э' || c == 'ю' || c == 'я');
}

// Функция удаления гласных
void remove_vowels(char *str, ssize_t length) {
    char *src = str;
    char *dst = str;
    
    for (ssize_t i = 0; i < length; i++) {
        if (!is_vowel(*src)) {
            *dst++ = *src;
        }
        src++;
    }
    // Не добавляем нулевой терминатор, так как работаем с бинарными данными
}

int main(int argc, char **argv) {
    char buf[4096];
    ssize_t bytes;

    pid_t pid = getpid();

    // NOTE: Открываем файл для записи
    int32_t file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (file == -1) {
        const char msg[] = "error: failed to open requested file\n";
        write(STDERR_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }

    while ((bytes = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        if (bytes < 0) {
            const char msg[] = "error: failed to read from stdin\n";
            write(STDERR_FILENO, msg, sizeof(msg));
            exit(EXIT_FAILURE);
        }

        // УДАЛЯЕМ ГЛАСНЫЕ вместо преобразования в верхний регистр
        remove_vowels(buf, bytes);

        // NOTE: Записываем в файл
        int32_t written = write(file, buf, bytes);
        if (written != bytes) {
            const char msg[] = "error: failed to write to file\n";
            write(STDERR_FILENO, msg, sizeof(msg));
            exit(EXIT_FAILURE);
        }
    }

    close(file);
    return 0;
}