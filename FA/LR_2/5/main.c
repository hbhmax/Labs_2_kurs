#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LENGHT_LINE 30

char* uniform_fill(const char* str, int new_len) {
    int len = strlen(str);
    
    if (new_len <= len) {
        return strdup(str);
    }

    int word_count = 0;
    int in_word = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ' && !in_word) {
            word_count++;
            in_word = 1;
        } else if (str[i] == ' ') {
            in_word = 0;
        }
    }

    if (word_count <= 1) {
        char* result = malloc(new_len + 1);
        strcpy(result, str);
        for (int i = len; i < new_len; i++) {
            result[i] = ' ';
        }
        result[new_len] = '\0';
        return result;
    }

    int total_spaces = new_len - len;
    int gaps = word_count - 1;
    int base_spaces = total_spaces / gaps;
    int extra_spaces = total_spaces % gaps;

    char* result = malloc(new_len + 1);
    char* ptr = result;
    int space_counter = 0;
    in_word = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ') {
            *ptr++ = str[i];
            in_word = 1;
        } else if (in_word) {
            int spaces_to_add = 1 + base_spaces + (space_counter < extra_spaces ? 1 : 0);
            for (int j = 0; j < spaces_to_add; j++) {
                *ptr++ = ' ';
            }
            space_counter++;
            in_word = 0;
        }
    }
    *ptr = '\0';
    return result;
}

char* slice_string(const char* str, int start, int end) {
    if (str == NULL || start < 0 || end < start) {
        return NULL;
    }
    
    int len = strlen(str);
    
    if (start > len) start = len;
    if (end > len) end = len;
    if (start < 0) start = len + start;
    if (end < 0) end = len + end;
    
    if (start < 0) start = 0;
    if (end < start) end = start;
    if (end > len) end = len;
    
    int slice_len = end - start;
    if (slice_len <= 0) {
        char* result = malloc(1);
        result[0] = '\0';
        return result;
    }
    
    char* result = malloc(slice_len + 1);
    if (result == NULL) return NULL;
    
    strncpy(result, str + start, slice_len);
    result[slice_len] = '\0';
    
    return result;
}

char** split_string_by_words(const char* str, int max_chars, int* count) {
    char* copy = strdup(str);
    if (!copy) return NULL;
    
    char** words = NULL;
    int word_count = 0;
    int capacity = 10;
    
    words = malloc(capacity * sizeof(char*));
    if (!words) {
        free(copy);
        return NULL;
    }
    
    char* token = strtok(copy, " ");
    while (token) {
        if (word_count >= capacity) {
            capacity *= 2;
            char** new_words = realloc(words, capacity * sizeof(char*));
            if (!new_words) {
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                free(copy);
                return NULL;
            }
            words = new_words;
        }
        
        words[word_count++] = strdup(token);
        token = strtok(NULL, " ");
    }
    free(copy);
    
    if (word_count == 0) {
        *count = 0;
        free(words);
        return NULL;
    }
    
    char** result = NULL;
    int result_count = 0;
    int result_capacity = 10;
    
    result = malloc(result_capacity * sizeof(char*));
    if (!result) {
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        free(words);
        return NULL;
    }
    
    int current_start = 0;
    
    while (current_start < word_count) {
        int current_len = 0;
        int word_index = current_start;
        
        while (word_index < word_count) {
            int word_len = strlen(words[word_index]);
            if (current_len + word_len + (current_len > 0 ? 1 : 0) <= max_chars) {
                current_len += word_len + (current_len > 0 ? 1 : 0);
                word_index++;
            } else {
                break;
            }
        }
        
        int substring_len = 0;
        for (int i = current_start; i < word_index; i++) {
            substring_len += strlen(words[i]) + (i > current_start ? 1 : 0);
        }
        
        char* substring = malloc(substring_len + 1);
        if (!substring) {
            for (int i = 0; i < result_count; i++) {
                free(result[i]);
            }
            free(result);
            for (int i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            return NULL;
        }
        
        substring[0] = '\0';
        for (int i = current_start; i < word_index; i++) {
            if (i > current_start) {
                strcat(substring, " ");
            }
            strcat(substring, words[i]);
        }
        
        if (result_count >= result_capacity) {
            result_capacity *= 2;
            char** new_result = realloc(result, result_capacity * sizeof(char*));
            if (!new_result) {
                free(substring);
                for (int i = 0; i < result_count; i++) {
                    free(result[i]);
                }
                free(result);
                for (int i = 0; i < word_count; i++) {
                    free(words[i]);
                }
                free(words);
                return NULL;
            }
            result = new_result;
        }
        
        result[result_count++] = substring;
        current_start = word_index;
    }
    
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
    
    *count = result_count;
    return result;
}

void free_string_array(char** arr, int count) {
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

int special_puts_str(char *input_path, char *output_path) {
    FILE *input_file = NULL;
    input_file = fopen(input_path, "r");
    if (!input_file) {
        printf("Error opening input file\n");
        return -1;
    }

    FILE *output_file = NULL;
    output_file = fopen(output_path, "w");
    if (!output_file) {
        printf("Error opening output file\n");
        fclose(input_file);
        return -1;
    }

    char line[1024];
    while (fgets(line, 1024, input_file)) {
        line[strcspn(line, "\n")] = '\0';
        
        char* copy = strdup(line);
        if (!copy) {
            printf("Memory allocation error\n");
            fclose(input_file);
            fclose(output_file);
            return -1;
        }
        
        char* token = strtok(copy, " ");
        while (token) {
            if (strlen(token) > MAX_LENGHT_LINE) {
                printf("Error: word '%s' contains %zu characters, which exceeds the maximum allowed (%d)\n", 
                       token, strlen(token), MAX_LENGHT_LINE);
                free(copy);
                fclose(input_file);
                fclose(output_file);
                return -1;
            }
            token = strtok(NULL, " ");
        }
        free(copy);

        if (strlen(line) < MAX_LENGHT_LINE) {
            fprintf(output_file, "%s\n", line);
        } else {
            int count_substr = 0;
            char **split_str = split_string_by_words(line, MAX_LENGHT_LINE, &count_substr);
            
            if (split_str) {
                for (int i = 0; i < count_substr; i++) {
                    char *temp_str = uniform_fill(split_str[i], MAX_LENGHT_LINE);
                    fprintf(output_file, "%s\n", temp_str);
                    free(temp_str);
                }
                free_string_array(split_str, count_substr);
            }
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}


int main() {
    char input_path[100];
    char output_path[100];

    printf("Input path to input file: ");
    scanf("%s", input_path);
    
    printf("Input path to output file: ");
    scanf("%s", output_path);

    int flag = special_puts_str(input_path, output_path);

    if (flag == 0) {
        printf("Successfully recorded in the file");
    } else {
        printf("An error occurred in writing to the file");
    }

    return 0;
}