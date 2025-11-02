#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_NAME_LENGTH 50
#define GRADES_COUNT 5

typedef struct {
    unsigned int id;
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char group[MAX_NAME_LENGTH];
    unsigned char grades[GRADES_COUNT];
} Student;

double calculate_average_grade(const Student *student);
void print_student(const Student *student);
void print_student_detailed(const Student *student);
void display_all_students(const Student *students, int count);

int search_by_id(const Student *students, int count, unsigned int id, Student *result);
int search_by_surname(const Student *students, int count, const char *surname, Student **results);
int search_by_name(const Student *students, int count, const char *name, Student **results);
int search_by_group(const Student *students, int count, const char *group, Student **results);

void save_student_to_file(FILE *output, const Student *student);
void save_top_students_to_file(FILE *output, const Student *students, int count);
int load_students(const char* filename, Student** students);

int compare_id(const void *a, const void *b);
int compare_surname(const void *a, const void *b);
int compare_name(const void *a, const void *b);
int compare_group(const void *a, const void *b);

void handle_search_by_id(const Student *students, int count);
void handle_search_by_surname(const Student *students, int count);
void handle_search_by_name(const Student *students, int count);
void handle_search_by_group(const Student *students, int count);
void handle_save_student_to_file(FILE *output, const Student *students, int count);
void handle_sort_by_id(Student *students, int count);
void handle_sort_by_surname(Student *students, int count);
void handle_sort_by_name(Student *students, int count);
void handle_sort_by_group(Student *students, int count);

char* extract_value(char* line, const char* field);
int extract_grades(char* line, unsigned char* grades);

#endif