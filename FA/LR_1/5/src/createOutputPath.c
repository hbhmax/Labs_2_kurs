#include <stdlib.h>
#include <string.h>
#include "../include/createOutputPath.h"

char * create_output_path(char * input_path) {

    const char* last_slash = strrchr(input_path, '/');
    const char* last_backslash = strrchr(input_path, '\\');
    const char* last_separator = NULL;
    
    // Выбираем последний разделитель
    if (last_slash && last_backslash) {
        last_separator = (last_slash > last_backslash) ? last_slash : last_backslash;
    } else if (last_slash) {
        last_separator = last_slash;
    } else if (last_backslash) {
        last_separator = last_backslash;
    }
    
    if (last_separator != NULL) {
        size_t dir_len = last_separator - input_path + 1;     // +1 чтобы включить разделитель
        size_t filename_len = strlen(last_separator + 1);
        size_t total_len = dir_len + 4 + filename_len + 1;    // 4 = "out_"
        
        char* new_path = (char*)malloc(total_len);
        if (new_path == NULL) return NULL;
        
        strncpy(new_path, input_path, dir_len);
        new_path[dir_len] = '\0';
        strcat(new_path, "out_");
        strcat(new_path, last_separator + 1);
        
        return new_path;
    } 
    else {
        size_t total_len = 4 + strlen(input_path) + 1;       // 4 = "out_"
        char* new_path = (char*)malloc(total_len);
        if (new_path == NULL) return NULL;
        
        strcpy(new_path, "out_");
        strcat(new_path, input_path);
        
        return new_path;
    }
}