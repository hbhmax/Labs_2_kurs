#include "include/functions.h"

int main(int argc, char const* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file> [output_file]\n", argv[0]);
        return -1;
    }

    Student* students = NULL;
    int student_count = load_students(argv[1], &students);
    
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
        printf("9. Save student by ID to file\n");
        printf("10. Save top students to file\n");
        printf("11. Show all students\n");
        printf("0. Exit\n");
        printf("Choose option: ");
        
        scanf("%d", &choice);

        if(choice < 0 || choice > 11) {
            printf("Invalid option\n");
            break;
        }
        
        switch (choice) {
            case 1:
                handle_search_by_id(students, student_count);
                break;
            case 2:
                handle_search_by_surname(students, student_count);
                break;
            case 3:
                handle_search_by_name(students, student_count);
                break;
            case 4:
                handle_search_by_group(students, student_count);
                break;
            case 5:
                handle_sort_by_id(students, student_count);
                break;
            case 6:
                handle_sort_by_surname(students, student_count);
                break;
            case 7:
                handle_sort_by_name(students, student_count);
                break;
            case 8:
                handle_sort_by_group(students, student_count);
                break;
            case 9:
                if (!output_file) {
                    printf("Output file not specified\n");
                    break;
                }
                handle_save_student_to_file(output_file, students, student_count);
                break;
            case 10:
                if (!output_file) {
                    printf("Output file not specified\n");
                    break;
                }
                save_top_students_to_file(output_file, students, student_count);
                printf("Results written to file\n");
                break;
            case 11:
                display_all_students(students, student_count);
                break;
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