#include <stdio.h>
#include <string.h>

#define MAX_LENGHT_LINE 30

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

int * find_space_indexes(const char* str, int* count) {
    *count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n') {
            (*count)++;
        }
    }
    
    int* indexes = (int*)malloc(*count * sizeof(int));
    if (indexes == NULL) {
        *count = 0;
        return NULL;
    }
    
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n') {
            indexes[index++] = i;
        }
    }
    return indexes;
}

int special_puts_str(const char* str, FILE * file) {
    char * temp_str = str;
    char * temp_line;
    int count_spaces;
    int * index_spaces = find_space_indexes(str, &count_spaces);

    if (count_spaces == 0) {
        fputs(temp_str, file);
    }

    int start = 0;
    int end;

    for (int i = 0; i < count_spaces; i++) {
        
    }
}

int main() {
    char input_path[100];
    char output_path[100];

    printf("Input path to input file: ");
    scanf("%s", input_path);
    
    printf("Input path to output file: ");
    scanf("%s", output_path);

    FILE * input_file = NULL;
    input_file = fopen(input_path, "r");
    if (!input_file) {
        printf("Error opening input file\n");
        return -1;
    }

    FILE * output_file = NULL;
    output_file = fopen(output_path, "w");
    if (!output_file) {
        printf("Error opening output file\n");
        return -1;
    }

    char line[1024];
    while (fgets(line, 1024, input_file)){
        if (strlen(line) < MAX_LENGHT_LINE) {
            fputs(line, output_file);
        } else {
            special_puts_str(line, output_file);
        }
    }
    

    fclose(input_file);
    fclose(output_file);

    return 0;
}