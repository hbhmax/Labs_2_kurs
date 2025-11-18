#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_LINE 256
#define VAR_COUNT 26

int variables[VAR_COUNT] = {0};

void remove_spaces(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int get_variable(char var) {
    return variables[var - 'A'];
}

void set_variable(char var, int value) {
    variables[var - 'A'] = value;
}

int is_variable(char c) {
    return (c >= 'A' && c <= 'Z');
}

int evaluate_expression(const char *expr) {
    char temp[MAX_LINE];
    strcpy(temp, expr);
    remove_spaces(temp);

    int start = 0, end = 0;
    for (int i = 0; i < strlen(temp); i++) {
        if (temp[i] == '(') start = i;
        if (temp[i] == ')') {
            end = i;
            break;
        }
    }

    if (start != 0 || end != 0) {
        char sub_expr[MAX_LINE];
        strncpy(sub_expr, temp + start + 1, end - start - 1);
        sub_expr[end - start - 1] = '\0';
        int result = evaluate_expression(sub_expr);
        
        char new_expr[MAX_LINE];
        strncpy(new_expr, temp, start);
        new_expr[start] = '\0';
        sprintf(new_expr + start, "%d%s", result, temp + end + 1);
        return evaluate_expression(new_expr);
    }

    if (isdigit(temp[0]) || (temp[0] == '-' && isdigit(temp[1]))) {
        return atoi(temp);
    }

    if (is_variable(temp[0]) && temp[1] == '\0') {
        return get_variable(temp[0]);
    }

    int len = strlen(temp);
    int op_pos = -1;
    char op = '\0';

    for (int i = len - 1; i >= 0; i--) {
        if (temp[i] == '^') {
            op_pos = i;
            op = '^';
            break;
        }
    }

    if (op_pos == -1) {
        for (int i = len - 1; i >= 0; i--) {
            if (temp[i] == '*' || temp[i] == '/') {
                op_pos = i;
                op = temp[i];
                break;
            }
        }
    }

    if (op_pos == -1) {
        for (int i = len - 1; i > 0; i--) {
            if (temp[i] == '+' || temp[i] == '-') {
                op_pos = i;
                op = temp[i];
                break;
            }
        }
    }

    if (op_pos == -1) {
        fprintf(stderr, "Error: invalid expression '%s'\n", expr);
        exit(1);
    }

    char left[MAX_LINE], right[MAX_LINE];
    strncpy(left, temp, op_pos);
    left[op_pos] = '\0';
    strcpy(right, temp + op_pos + 1);

    int left_val = evaluate_expression(left);
    int right_val = evaluate_expression(right);

    switch (op) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': 
            if (right_val == 0) {
                fprintf(stderr, "Error: division by zero\n");
                exit(1);
            }
            return left_val / right_val;
        case '^': return (int)pow(left_val, right_val);
        default:
            fprintf(stderr, "Error: unknown operator '%c'\n", op);
            exit(1);
    }
}

void log_operation(FILE *log_file, int line_num, const char *command, const char *operation) {
    fprintf(log_file, "[%d] %s | ", line_num, command);

    int first = 1;
    for (int i = 0; i < VAR_COUNT; i++) {
        if (variables[i] != 0 || first) { // Выводим хотя бы одну переменную
            if (!first) fprintf(log_file, ", ");
            fprintf(log_file, "%c=%d", 'A' + i, variables[i]);
            first = 0;
        }
    }
    fprintf(log_file, " | %s\n", operation);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    FILE *log_file = fopen("trace.log", "w");
    if (!log_file) {
        perror("Error creating log file");
        fclose(input_file);
        return 1;
    }

    char line[MAX_LINE];
    int line_num = 0;

    while (fgets(line, sizeof(line), input_file)) {
        line_num++;
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) == 0) continue;

        char temp[MAX_LINE];
        strcpy(temp, line);
        char *start = temp;
        while (isspace(*start)) start++;
        char *end = temp + strlen(temp) - 1;
        while (end > start && isspace(*end)) *end-- = '\0';

        if (strstr(temp, "print(") == temp) {
            char *open_paren = strchr(temp, '(');
            if (open_paren) {
                char *close_paren = strchr(open_paren, ')');
                if (close_paren) {
                    char var = open_paren[1];
                    if (var >= 'A' && var <= 'Z' && close_paren[0] == ')') {
                        int value = get_variable(var);
                        printf("%d\n", value);
                        log_operation(log_file, line_num, line, "Print " + var);
                    } else {
                        fprintf(stderr, "Error: invalid print command at line %d\n", line_num);
                    }
                }
            }
        } else {
            char *equals = strchr(temp, '=');
            if (equals) {
                char var = temp[0];
                if (is_variable(var)) {
                    char expr[MAX_LINE];
                    strcpy(expr, equals + 1);
                    int result = evaluate_expression(expr);
                    set_variable(var, result);

                    if (strchr(expr, '+') || strchr(expr, '-') || 
                        strchr(expr, '*') || strchr(expr, '/') ||
                        strchr(expr, '^')) {
                        log_operation(log_file, line_num, line, "Arithmetic operation");
                    } else {
                        log_operation(log_file, line_num, line, "Assignment");
                    }
                } else {
                    fprintf(stderr, "Error: invalid variable name at line %d\n", line_num);
                }
            } else {
                fprintf(stderr, "Error: invalid command at line %d\n", line_num);
            }
        }
    }

    fclose(input_file);
    fclose(log_file);
    return 0;
}