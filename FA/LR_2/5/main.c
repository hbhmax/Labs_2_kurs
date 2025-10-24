#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_readable_char(char c) {
    return isalnum(c) || strchr("!@#$%^&*()_+-={}|;:',.<>?/~`", c) != NULL;
}

void process_line(FILE *out, const char *line) {
    const int MAX_LENGTH = 80;
    char *buffer = malloc(MAX_LENGTH + 1);
    if (!buffer) {
        perror("Memory allocation error");
        return;
    }
    
    const char *start = line;
    const char *end = line;
    int length = 0;
    
    while (*end) {
        while (*end && !isspace(*end)) end++;
        
        if (length + (end - start) <= MAX_LENGTH) {
            strncpy(buffer + length, start, end - start);
            length += end - start;
            
            if (length < MAX_LENGTH && *end) {
                buffer[length++] = ' ';
            }
            
            start = end + 1;
            end = start;
        } else {
            int spaces_needed = MAX_LENGTH - length;
            int word_count = 0;
            const char *word_start = line;
            
            while (word_start < start) {
                while (*word_start && isspace(*word_start)) word_start++;
                if (*word_start) word_count++;
                while (*word_start && !isspace(*word_start)) word_start++;
            }
            
            int base_spaces = spaces_needed / (word_count - 1);
            int extra_spaces = spaces_needed % (word_count - 1);
            
            fputs(buffer, out);
            fputc('\n', out);
            
            memset(buffer, 0, MAX_LENGTH + 1);
            length = 0;
        }
    }
    
    if (length > 0) {
        fputs(buffer, out);
        fputc('\n', out);
    }
    
    free(buffer);
}

int main() {
    char input_path[256];
    char output_path[256];
    
    printf("Enter input file path: ");
    fgets(input_path, sizeof(input_path), stdin);
    input_path[strcspn(input_path, "\n")] = 0;
    
    printf("Enter output file path: ");
    fgets(output_path, sizeof(output_path), stdin);
    output_path[strcspn(output_path, "\n")] = 0;
    
    FILE *in_file = fopen(input_path, "r");
    if (!in_file) {
        perror("Error opening input file");
        return 1;
    }
    
    FILE *out_file = fopen(output_path, "w");
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