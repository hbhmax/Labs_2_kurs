#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    unsigned int id;
    char name[50];
    char surname[50];
    char group[50];
    unsigned char grades[5];
} Student;

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

void search_by_id(Student *students, int count, unsigned int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Found - ID: %u, NAME: %s, SURNAME: %s, GROUP: %s\n", 
                   students[i].id, students[i].name, students[i].surname, students[i].group);
            return;
        }
    }
    printf("Student with ID %u not found\n", id);
}

void search_by_surname(Student *students, int count, const char *surname) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].surname, surname) == 0) {
            printf("Found - ID: %u, NAME: %s, SURNAME: %s, GROUP: %s\n", 
                   students[i].id, students[i].name, students[i].surname, students[i].group);
            found = 1;
        }
    }
    if (!found) printf("Student with surname %s not found\n", surname);
}

void search_by_name(Student *students, int count, const char *name) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Found - ID: %u, NAME: %s, SURNAME: %s, GROUP: %s\n", 
                   students[i].id, students[i].name, students[i].surname, students[i].group);
            found = 1;
        }
    }
    if (!found) printf("Student with name %s not found\n", name);
}

void search_by_group(Student *students, int count, const char *group) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            printf("Found - ID: %u, NAME: %s, SURNAME: %s, GROUP: %s\n", 
                   students[i].id, students[i].name, students[i].surname, students[i].group);
            found = 1;
        }
    }
    if (!found) printf("No students in group %s\n", group);
}

void print_student_by_id(FILE *output, Student *students, int count, unsigned int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            double sum = 0;
            for (int j = 0; j < 5; j++) {
                sum += students[i].grades[j];
            }
            double avg = sum / 5;
            fprintf(output, "Student: %s %s, Group: %s, Average grade: %.2f\n", 
                    students[i].surname, students[i].name, students[i].group, avg);
            return;
        }
    }
    fprintf(output, "Student with ID %u not found\n", id);
}

void print_top_students(FILE *output, Student *students, int count) {
    if (count == 0) {
        fprintf(output, "No students found\n");
        return;
    }
    
    double total_avg = 0;
    for (int i = 0; i < count; i++) {
        double sum = 0;
        for (int j = 0; j < 5; j++) {
            sum += students[i].grades[j];
        }
        total_avg += sum / 5;
    }
    total_avg /= count;
    
    fprintf(output, "Students with average grade above %.2f:\n", total_avg);
    int found_above_avg = 0;
    for (int i = 0; i < count; i++) {
        double sum = 0;
        for (int j = 0; j < 5; j++) {
            sum += students[i].grades[j];
        }
        double avg = sum / 5;
        if (avg > total_avg) {
            fprintf(output, "  %s %s (%.2f)\n", students[i].surname, students[i].name, avg);
            found_above_avg = 1;
        }
    }
    
    if (!found_above_avg) {
        fprintf(output, "  No students with average grade above %.2f\n", total_avg);
    }
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
    
    while (*ptr && *ptr != ']' && grade_count < 5) {
        if (isdigit(*ptr)) {
            grades[grade_count++] = *ptr - '0';
        }
        ptr++;
    }
    
    return grade_count == 5;
}

int readStudents(const char* filename, Student** students) {
    FILE* file = fopen(filename, "r");
    if (!file) return -1;
    
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
    int fields_found = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strlen(line) <= 1) {
            if (fields_found == 0x1F) {
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
            fields_found = 0;
            continue;
        }
        
        char* id_value = extract_value(line, "ID:");
        if (id_value) {
            current.id = atoi(id_value);
            fields_found |= 0x01;
        }
        
        char* name_value = extract_value(line, "NAME:");
        if (name_value) {
            char* end = name_value;
            while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                end++;
            }
            int len = end - name_value;
            if (len > 0) {
                strncpy(current.name, name_value, len);
                current.name[len] = '\0';
                fields_found |= 0x02;
            }
        }
        
        char* surname_value = extract_value(line, "SURNAME:");
        if (surname_value) {
            char* end = surname_value;
            while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                end++;
            }
            int len = end - surname_value;
            if (len > 0) {
                strncpy(current.surname, surname_value, len);
                current.surname[len] = '\0';
                fields_found |= 0x04;
            }
        }
        
        char* group_value = extract_value(line, "GROUP:");
        if (group_value) {
            char* end = group_value;
            while (*end && !isspace(*end) && *end != ',' && *end != ';') {
                end++;
            }
            int len = end - group_value;
            if (len > 0) {
                strncpy(current.group, group_value, len);
                current.group[len] = '\0';
                fields_found |= 0x08;
            }
        }
        
        if (strstr(line, "GRADES:")) {
            if (extract_grades(line, current.grades)) {
                fields_found |= 0x10;
            }
        }
    }
    
    if (fields_found == 0x1F) {
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

void print_students(Student* students, int count) {
    printf("\n=== Student List (%d students) ===\n", count);
    for (int i = 0; i < count; i++) {
        printf("ID: %u, NAME: %s, SURNAME: %s, GROUP: %s, GRADES: [%d, %d, %d, %d, %d]\n",
               students[i].id, students[i].name, students[i].surname, students[i].group,
               students[i].grades[0], students[i].grades[1], students[i].grades[2],
               students[i].grades[3], students[i].grades[4]);
    }
    printf("==================================\n");
}

int main(int argc, char const* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file> [output_file]\n", argv[0]);
        return -1;
    }

    Student* students = NULL;
    int student_count = readStudents(argv[1], &students);
    
    if (student_count <= 0) {
        printf("No valid students found or error reading file\n");
        if (students) free(students);
        return -1;
    }

    FILE* output_file = NULL;
    if (argc == 3) {
        output_file = fopen(argv[2], "w");
        if (!output_file) {
            printf("Error opening output file\n");
        }
    }

    printf("Successfully loaded %d students\n", student_count);
    
    int choice;
    do {
        printf("\n=== Student Database ===\n");
        printf("1. Search by ID\n");
        printf("2. Search by surname\n");
        printf("3. Search by name\n");
        printf("4. Search by group\n");
        printf("5. Sort by ID\n");
        printf("6. Sort by surname\n");
        printf("7. Sort by name\n");
        printf("8. Sort by group\n");
        printf("9. Print student by ID to file\n");
        printf("10. Print top students to file\n");
        printf("11. Show all students\n");
        printf("0. Exit\n");
        printf("Choose option: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                unsigned int id;
                printf("Enter ID: ");
                scanf("%u", &id);
                search_by_id(students, student_count, id);
                break;
            }
            case 2: {
                char surname[50];
                printf("Enter surname: ");
                scanf("%49s", surname);
                search_by_surname(students, student_count, surname);
                break;
            }
            case 3: {
                char name[50];
                printf("Enter name: ");
                scanf("%49s", name);
                search_by_name(students, student_count, name);
                break;
            }
            case 4: {
                char group[50];
                printf("Enter group: ");
                scanf("%49s", group);
                search_by_group(students, student_count, group);
                break;
            }
            case 5: {
                qsort(students, student_count, sizeof(Student), compare_id);
                printf("Sorted by ID\n");
                print_students(students, student_count);
                break;
            }
            case 6: {
                qsort(students, student_count, sizeof(Student), compare_surname);
                printf("Sorted by surname\n");
                print_students(students, student_count);
                break;
            }
            case 7: {
                qsort(students, student_count, sizeof(Student), compare_name);
                printf("Sorted by name\n");
                print_students(students, student_count);
                break;
            }
            case 8: {
                qsort(students, student_count, sizeof(Student), compare_group);
                printf("Sorted by group\n");
                print_students(students, student_count);
                break;
            }
            case 9: {
                if (!output_file) {
                    printf("Output file not specified\n");
                    break;
                }
                unsigned int id;
                printf("Enter student ID: ");
                scanf("%u", &id);
                print_student_by_id(output_file, students, student_count, id);
                printf("Result written to file\n");
                break;
            }
            case 10: {
                if (!output_file) {
                    printf("Output file not specified\n");
                    break;
                }
                print_top_students(output_file, students, student_count);
                printf("Results written to file\n");
                break;
            }
            case 11: {
                print_students(students, student_count);
                break;
            }
            case 0:
                printf("End\n");
                break;
            default:
                printf("Invalid option\n");
        }
    } while (choice != 0);

    free(students);
    if (output_file) fclose(output_file);
    
    return 0;
}