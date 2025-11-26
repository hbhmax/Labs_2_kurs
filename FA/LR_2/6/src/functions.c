#include "../include/functions.h"

int is_latin_string(const char *str) {
    if (!str || strlen(str) == 0) return 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || 
              (str[i] >= 'a' && str[i] <= 'z') ||
              str[i] == ' ' || str[i] == '-')) {
            return 0;
        }
    }
    return 1;
}

double calculate_average_grade(const Student *student) {
    double sum = 0;
    for (int i = 0; i < GRADES_COUNT; i++) {
        sum += student->grades[i];
    }
    return sum / GRADES_COUNT;
}

void print_student(const Student *student) {
    printf("ID: %u, NAME: %s, SURNAME: %s, GROUP: %s\n", 
           student->id, student->name, student->surname, student->group);
}

void print_student_detailed(const Student *student) {
    double avg = calculate_average_grade(student);
    printf("ID: %u, NAME: %s, SURNAME: %s, GROUP: %s, GRADES: [%d, %d, %d, %d, %d], AVG: %.2f\n",
           student->id, student->name, student->surname, student->group,
           student->grades[0], student->grades[1], student->grades[2],
           student->grades[3], student->grades[4], avg);
}

void display_all_students(const Student *students, int count) {
    printf("\n=== Student List (%d students) ===\n", count);
    for (int i = 0; i < count; i++) {
        print_student_detailed(&students[i]);
    }
    printf("==================================\n");
}

int search_by_id(const Student *students, int count, unsigned int id, Student *result) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            *result = students[i];
            return 1;
        }
    }
    return 0;
}

int search_by_surname(const Student *students, int count, const char *surname, Student **results) {
    int found_count = 0;
    *results = NULL;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].surname, surname) == 0) {
            found_count++;
        }
    }
    
    if (found_count > 0) {
        *results = malloc(found_count * sizeof(Student));
        int index = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].surname, surname) == 0) {
                (*results)[index++] = students[i];
            }
        }
    }
    
    return found_count;
}

int search_by_name(const Student *students, int count, const char *name, Student **results) {
    int found_count = 0;
    *results = NULL;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            found_count++;
        }
    }
    
    if (found_count > 0) {
        *results = malloc(found_count * sizeof(Student));
        int index = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].name, name) == 0) {
                (*results)[index++] = students[i];
            }
        }
    }
    
    return found_count;
}

int search_by_group(const Student *students, int count, const char *group, Student **results) {
    int found_count = 0;
    *results = NULL;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            found_count++;
        }
    }
    
    if (found_count > 0) {
        *results = malloc(found_count * sizeof(Student));
        int index = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].group, group) == 0) {
                (*results)[index++] = students[i];
            }
        }
    }
    
    return found_count;
}

void save_student_to_file(FILE *output, const Student *student) {
    double avg = calculate_average_grade(student);
    fprintf(output, "Student: %s %s, Group: %s, Average grade: %.2f\n", 
            student->surname, student->name, student->group, avg);
}

void save_top_students_to_file(FILE *output, const Student *students, int count) {
    if (count == 0) {
        fprintf(output, "No students found\n");
        return;
    }
    
    double total_avg = 0;
    for (int i = 0; i < count; i++) {
        total_avg += calculate_average_grade(&students[i]);
    }
    total_avg /= count;
    
    fprintf(output, "Students with average grade above %.2f:\n", total_avg);
    int found_above_avg = 0;
    for (int i = 0; i < count; i++) {
        double avg = calculate_average_grade(&students[i]);
        if (avg > total_avg) {
            fprintf(output, "  %s %s (%.2f)\n", students[i].surname, students[i].name, avg);
            found_above_avg = 1;
        }
    }
    
    if (!found_above_avg) {
        fprintf(output, "  No students with average grade above %.2f\n", total_avg);
    }
}

int compare_id(const void *a, const void *b) {
    const Student *s1 = (const Student*)a;
    const Student *s2 = (const Student*)b;
    return s1->id - s2->id;
}

int compare_surname(const void *a, const void *b) {
    const Student *s1 = (const Student*)a;
    const Student *s2 = (const Student*)b;
    return strcmp(s1->surname, s2->surname);
}

int compare_name(const void *a, const void *b) {
    const Student *s1 = (const Student*)a;
    const Student *s2 = (const Student*)b;
    return strcmp(s1->name, s2->name);
}

int compare_group(const void *a, const void *b) {
    const Student *s1 = (const Student*)a;
    const Student *s2 = (const Student*)b;
    return strcmp(s1->group, s2->group);
}

void handle_search_by_id(const Student *students, int count) {
    unsigned int id;
    printf("Enter ID: ");
    scanf("%u", &id);
    
    Student result;
    if (search_by_id(students, count, id, &result)) {
        printf("Found: ");
        print_student_detailed(&result);
    } else {
        printf("Student with ID %u not found\n", id);
    }
}

void handle_search_by_surname(const Student *students, int count) {
    char surname[MAX_NAME_LENGTH];
    printf("Enter surname: ");
    scanf("%49s", surname);
    
    Student *results;
    int found_count = search_by_surname(students, count, surname, &results);
    if (found_count > 0) {
        printf("Found %d students:\n", found_count);
        for (int i = 0; i < found_count; i++) {
            print_student_detailed(&results[i]);
        }
        free(results);
    } else {
        printf("Student with surname %s not found\n", surname);
    }
}

void handle_search_by_name(const Student *students, int count) {
    char name[MAX_NAME_LENGTH];
    printf("Enter name: ");
    scanf("%49s", name);
    
    Student *results;
    int found_count = search_by_name(students, count, name, &results);
    if (found_count > 0) {
        printf("Found %d students:\n", found_count);
        for (int i = 0; i < found_count; i++) {
            print_student_detailed(&results[i]);
        }
        free(results);
    } else {
        printf("Student with name %s not found\n", name);
    }
}

void handle_search_by_group(const Student *students, int count) {
    char group[MAX_NAME_LENGTH];
    printf("Enter group: ");
    scanf("%49s", group);
    
    Student *results;
    int found_count = search_by_group(students, count, group, &results);
    if (found_count > 0) {
        printf("Found %d students in group %s:\n", found_count, group);
        for (int i = 0; i < found_count; i++) {
            print_student(&results[i]);
        }
        free(results);
    } else {
        printf("No students in group %s\n", group);
    }
}

void handle_save_student_to_file(FILE *output, const Student *students, int count) {
    unsigned int id;
    printf("Enter student ID: ");
    scanf("%u", &id);
    
    Student result;
    if (search_by_id(students, count, id, &result)) {
        save_student_to_file(output, &result);
        printf("Result written to file\n");
    } else {
        fprintf(output, "Student with ID %u not found\n", id);
        printf("Student not found\n");
    }
}

void handle_sort_by_id(Student *students, int count) {
    qsort(students, count, sizeof(Student), compare_id);
    printf("Sorted by ID\n");
    display_all_students(students, count);
}

void handle_sort_by_surname(Student *students, int count) {
    qsort(students, count, sizeof(Student), compare_surname);
    printf("Sorted by surname\n");
    display_all_students(students, count);
}

void handle_sort_by_name(Student *students, int count) {
    qsort(students, count, sizeof(Student), compare_name);
    printf("Sorted by name\n");
    display_all_students(students, count);
}

void handle_sort_by_group(Student *students, int count) {
    qsort(students, count, sizeof(Student), compare_group);
    printf("Sorted by group\n");
    display_all_students(students, count);
}

char* extract_value(char* line, const char* field) {
    char* field_pos = strstr(line, field);
    if (!field_pos) return NULL;
    
    char* value_start = field_pos + strlen(field);
    while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
        value_start++;
    }
    
    return value_start;
}

int extract_grades(char* line, unsigned char* grades) {
    char* grades_start = strstr(line, "GRADES:");
    if (!grades_start) return 0;
    
    char* bracket_start = strchr(grades_start, '[');
    if (!bracket_start) return 0;
    
    char* ptr = bracket_start + 1;
    int grade_count = 0;
    
    while (*ptr && *ptr != ']' && grade_count < GRADES_COUNT) {
        if (isdigit(*ptr)) {
            grades[grade_count++] = *ptr - '0';
        }
        ptr++;
    }
    
    return grade_count == GRADES_COUNT;
}

int load_students(const char* filename, Student** students) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return -1;
    }
    
    *students = NULL;
    int count = 0;
    int capacity = 10;
    *students = malloc(capacity * sizeof(Student));
    if (!*students) {
        fclose(file);
        return -1;
    }
    
    char line[256];
    Student current = {0};
    int has_id = 0, has_name = 0, has_surname = 0, has_group = 0, has_grades = 0;
    int valid_name = 1, valid_surname = 1;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) <= 1) {
            if (has_id && has_name && has_surname && has_group && has_grades && 
                valid_name && valid_surname) {
                if (count >= capacity) {
                    capacity *= 2;
                    Student* temp = realloc(*students, capacity * sizeof(Student));
                    if (!temp) {
                        fclose(file);
                        free(*students);
                        return -1;
                    }
                    *students = temp;
                }
                (*students)[count++] = current;
            }
            memset(&current, 0, sizeof(Student));
            has_id = has_name = has_surname = has_group = has_grades = 0;
            valid_name = valid_surname = 1;
            continue;
        }
        
        int fields_in_line = 0;
        if (strstr(line, "ID:") && strstr(line, "NAME:") && strstr(line, "SURNAME:") && 
            strstr(line, "GROUP:") && strstr(line, "GRADES:")) {
            fields_in_line = 1;
        }
        
        if (fields_in_line) {
            char* ptr = line;
            
            char* id_start = strstr(ptr, "ID:");
            if (id_start && !has_id) {
                char* value_start = id_start + 3;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* end = value_start;
                while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                    end++;
                }
                int len = end - value_start;
                if (len > 0) {
                    char id_str[20];
                    strncpy(id_str, value_start, len);
                    id_str[len] = '\0';
                    
                    char* endptr;
                    errno = 0;
                    double id_d = strtod(id_str, &endptr);
                    if (errno == 0 && endptr != id_str && id_d >= 0) {
                        current.id = (unsigned int)id_d;
                        has_id = 1;
                    }
                }
            }
            
            char* name_start = strstr(ptr, "NAME:");
            if (name_start && !has_name) {
                char* value_start = name_start + 5;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* end = value_start;
                while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                    end++;
                }
                int len = end - value_start;
                if (len > 0 && len < MAX_NAME_LENGTH) {
                    strncpy(current.name, value_start, len);
                    current.name[len] = '\0';
                    if (is_latin_string(current.name)) {
                        has_name = 1;
                        valid_name = 1;
                    } else {
                        has_name = 0;
                        valid_name = 0;
                    }
                }
            }
            
            char* surname_start = strstr(ptr, "SURNAME:");
            if (surname_start && !has_surname) {
                char* value_start = surname_start + 8;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* end = value_start;
                while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                    end++;
                }
                int len = end - value_start;
                if (len > 0 && len < MAX_NAME_LENGTH) {
                    strncpy(current.surname, value_start, len);
                    current.surname[len] = '\0';
                    if (is_latin_string(current.surname)) {
                        has_surname = 1;
                        valid_surname = 1;
                    } else {
                        has_surname = 0;
                        valid_surname = 0;
                    }
                }
            }
            
            char* group_start = strstr(ptr, "GROUP:");
            if (group_start && !has_group) {
                char* value_start = group_start + 6;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* end = value_start;
                while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                    end++;
                }
                int len = end - value_start;
                if (len > 0 && len < MAX_NAME_LENGTH) {
                    strncpy(current.group, value_start, len);
                    current.group[len] = '\0';
                    has_group = 1;
                }
            }
            
            if (!has_grades) {
                if (extract_grades(line, current.grades)) {
                    has_grades = 1;
                }
            }
        } else {
            if (strncmp(line, "ID:", 3) == 0 && !has_id) {
                char* value_start = line + 3;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* endptr;
                errno = 0;
                double id_d = strtod(value_start, &endptr);
                
                if (errno == 0 && endptr != value_start && id_d >= 0) {
                    current.id = (unsigned int)id_d;
                    has_id = 1;
                }
            } 
            else if (strncmp(line, "NAME:", 5) == 0 && !has_name) {
                char* value_start = line + 5;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* end = value_start;
                while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                    end++;
                }
                int len = end - value_start;
                if (len > 0 && len < MAX_NAME_LENGTH) {
                    strncpy(current.name, value_start, len);
                    current.name[len] = '\0';
                    if (is_latin_string(current.name)) {
                        has_name = 1;
                        valid_name = 1;
                    } else {
                        has_name = 0;
                        valid_name = 0;
                    }
                }
            } 
            else if (strncmp(line, "SURNAME:", 8) == 0 && !has_surname) {
                char* value_start = line + 8;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* end = value_start;
                while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                    end++;
                }
                int len = end - value_start;
                if (len > 0 && len < MAX_NAME_LENGTH) {
                    strncpy(current.surname, value_start, len);
                    current.surname[len] = '\0';
                    if (is_latin_string(current.surname)) {
                        has_surname = 1;
                        valid_surname = 1;
                    } else {
                        has_surname = 0;
                        valid_surname = 0;
                    }
                }
            } 
            else if (strncmp(line, "GROUP:", 6) == 0 && !has_group) {
                char* value_start = line + 6;
                while (*value_start && (isspace(*value_start) || *value_start == ',' || *value_start == ';')) {
                    value_start++;
                }
                
                char* end = value_start;
                while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                    end++;
                }
                int len = end - value_start;
                if (len > 0 && len < MAX_NAME_LENGTH) {
                    strncpy(current.group, value_start, len);
                    current.group[len] = '\0';
                    has_group = 1;
                }
            } 
            else if (strncmp(line, "GRADES:", 7) == 0 && !has_grades) {
                if (extract_grades(line, current.grades)) {
                    has_grades = 1;
                }
            }
        }
    }
    
    if (has_id && has_name && has_surname && has_group && has_grades && 
        valid_name && valid_surname) {
        if (count >= capacity) {
            capacity += 1;
            Student* temp = realloc(*students, capacity * sizeof(Student));
            if (temp) {
                *students = temp;
            }
        }
        (*students)[count++] = current;
    }
    
    fclose(file);
    return count;
}