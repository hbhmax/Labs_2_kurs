#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_readable_char(char c) {
    return isalnum((unsigned char)c) || 
           (c >= 33 && c <= 47) ||  // !"#$%&'()*+,-./
           (c >= 58 && c <= 64) ||  // :;<=>?@
           (c >= 91 && c <= 96) || // [\]^_`
           (c >= 123 && c <= 126); // {|}~
}

char** split_into_words(const char* line, int* word_count) {
    *word_count = 0;
    char** words = NULL;
    int capacity = 10;

    words = malloc(capacity * sizeof(char*));
    if (!words) return NULL;

    char* copy = strdup(line);
    if (!copy) {
        free(words);
        return NULL;
    }

    char* token = strtok(copy, " \t\n");
    while (token) {
        if (*word_count >= capacity) {
            capacity *= 2;
            char** temp = realloc(words, capacity * sizeof(char*));
            if (!temp) {
                free(copy);
                for (int i = 0; i < *word_count; i++) free(words[i]);
                free(words);
                return NULL;
            }
            words = temp;
        }
        words[*word_count] = strdup(token);
        if (!words[*word_count]) {
            free(copy);
            for (int i = 0; i < *word_count; i++) free(words[i]);
            free(words);
            return NULL;
        }
        (*word_count)++;
        token = strtok(NULL, " \t\n");
    }

    free(copy);
    return words;
}

int calculate_line_length(char** words, int start, int end) {
    int length = 0;
    for (int i = start; i <= end; i++) {
        length += strlen(words[i]);
        if (i < end) length++;
    }
    return length;
}

void process_line(FILE* out, const char* line) {
    const int MAX_LENGTH = 80;
    int word_count;
    char** words = split_into_words(line, &word_count);

    if (!words || word_count == 0) {
        fputc('\n', out);
        free(words);
        return;
    }

    int start = 0;
    while (start < word_count) {
        int end = start;
        int current_length = strlen(words[start]);

        while (end + 1 < word_count) {
            int next_length = current_length + 1 + strlen(words[end + 1]);
            if (next_length <= MAX_LENGTH) {
                current_length = next_length;
                end++;
            } else {
                break;
            }
        }

        if (end == word_count - 1 || start == end) {
            for (int i = start; i <= end; i++) {
                fputs(words[i], out);
                if (i < end) fputc(' ', out);
            }
            fputc('\n', out);
        } else {
            int total_chars = 0;
            for (int i = start; i <= end; i++) {
                total_chars += strlen(words[i]);
            }

            int total_spaces = MAX_LENGTH - total_chars;
            int gap_count = end - start;

            if (gap_count == 0) {
                fputs(words[start], out);
                fputc('\n', out);
            } else {
                int base_spaces = total_spaces / gap_count;
                int extra_spaces = total_spaces % gap_count;

                fputs(words[start], out);

                for (int i = start + 1; i <= end; i++) {
                    int spaces_here = base_spaces;
                    if (i - start <= extra_spaces) {
                        spaces_here++;
                    }

                    for (int j = 0; j < spaces_here; j++) {
                        fputc(' ', out);
                    }

                    fputs(words[i], out);
                }
                fputc('\n', out);
            }
        }

        start = end + 1;
    }

    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
}

int main() {
    char input_path[256];
    char output_path[256];

    printf("Enter input file path: ");
    if (!fgets(input_path, sizeof(input_path), stdin)) {
        fprintf(stderr, "Error reading input path\n");
        return 1;
    }
    input_path[strcspn(input_path, "\n")] = 0;

    printf("Enter output file path: ");
    if (!fgets(output_path, sizeof(output_path), stdin)) {
        fprintf(stderr, "Error reading output path\n");
        return 1;
    }
    output_path[strcspn(output_path, "\n")] = 0;

    FILE* in_file = fopen(input_path, "r");
    if (!in_file) {
        perror("Error opening input file");
        return 1;
    }

    FILE* out_file = fopen(output_path, "w");
    if (!out_file) {
        perror("Error opening output file");
        fclose(in_file);
        return 1;
    }

    char line[4096];
    while (fgets(line, sizeof(line), in_file)) {
        line[strcspn(line, "\n")] = 0;
        process_line(out_file, line);
    }
    
    fclose(in_file);
    fclose(out_file);
    
    printf("Processing completed successfully.\n");
    return 0;
}