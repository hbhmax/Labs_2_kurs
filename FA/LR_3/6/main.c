#include <stdio.h>

int check_brackets(const char *str) {
    char stack[100];
    int top = -1;

    while (*str) {
        char c = *str;

        if (c == '(' || c == '[' || c == '{' || c == '<') {
            if (top >= 99) {
                return 0;
            }
            stack[++top] = c;
        }
        else if (c == ')' || c == ']' || c == '}' || c == '>') {
            if (top == -1) {
                return 0;
            }

            char open = stack[top];
            top--;

            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{') ||
                (c == '>' && open != '<')) {
                return 0;
            }
        }

        str++;
    }

    return (top == -1) ? 1 : 0;
}

int main() {
    const char *tests[] = {
        "()",           // 1 — верно
        "([])",         // 1 — верно
        "{[()]}",       // 1 — верно
        "<>",           // 1 — верно
        "(()",          // 0 — не закрыта
        "())",          // 0 — лишняя закрывающая
        "([)]",         // 0 — неверный порядок
        "{[}]",         // 0 — неверный порядок
        "",             // 1 — пустая строка
        "abc123",      // 1 — нет скобок
        "a(b[c{d<e>f}g]h)i", // 1 — верно
        "(]",           // 0 — несоответствие
        "[)",           // 0 — несоответствие
        "({<]>})",     // 0 — неверный порядок
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        printf("\"%s\" -> %d\n", tests[i], check_brackets(tests[i]));
    }

    return 0;
}
