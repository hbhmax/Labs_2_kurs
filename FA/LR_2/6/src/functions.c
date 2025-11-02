#include "../include/functions.h"

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
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) <= 1) {
            if (has_id && has_name && has_surname && has_group && has_grades) {
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
            continue;
        }
        
        char* id_value = extract_value(line, "ID:");
        if (id_value && !has_id) {
            char* endptr;
            errno = 0;
            double id_d = strtod(id_value, &endptr);
            
            if (errno == 0 && endptr != id_value && id_d >= 0) {
                current.id = (unsigned int)id_d;
                has_id = 1;
            }
        }
        
        char* name_value = extract_value(line, "NAME:");
        if (name_value && !has_name) {
            char* end = name_value;
            while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                end++;
            }
            int len = end - name_value;
            if (len > 0 && len < MAX_NAME_LENGTH) {
                strncpy(current.name, name_value, len);
                current.name[len] = '\0';
                has_name = 1;
            }
        }
        
        char* surname_value = extract_value(line, "SURNAME:");
        if (surname_value && !has_surname) {
            char* end = surname_value;
            while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                end++;
            }
            int len = end - surname_value;
            if (len > 0 && len < MAX_NAME_LENGTH) {
                strncpy(current.surname, surname_value, len);
                current.surname[len] = '\0';
                has_surname = 1;
            }
        }
        
        char* group_value = extract_value(line, "GROUP:");
        if (group_value && !has_group) {
            char* end = group_value;
            while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                end++;
            }
            int len = end - group_value;
            if (len > 0 && len < MAX_NAME_LENGTH) {
                strncpy(current.group, group_value, len);
                current.group[len] = '\0';
                has_group = 1;
            }
        }
        
        if (strstr(line, "GRADES:") && !has_grades) {
            if (extract_grades(line, current.grades)) {
                has_grades = 1;
            }
        }
    }
    
    if (has_id && has_name && has_surname && has_group && has_grades) {
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