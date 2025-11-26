#include <stdio.h>
#include "include/functions.h"

int main() {
    int l;
    printf("\n--- overfprintf ---\n");
    l = overfprintf(stdout, "Number %d in Roman numerals: %Ro\n", 45, 45);
    printf("%d\n", l);
    l = overfprintf(stdout, "Number %u in Zeckendorf representation: %Zr\n", 431, 431);
    printf("%d\n", l);
    l = overfprintf(stdout, "Number %d in base %d: %Cv\n", 67, 14, 67, 14);
    printf("%d\n", l);
    l = overfprintf(stdout, "Number %d in base %d: %CV\n", 67, 14, 67, 14);
    printf("%d\n", l);
    l = overfprintf(stdout, "Number %to - its %s in base %d\n", "3a", 12, "3a", 12);
    printf("%d\n", l);
    l = overfprintf(stdout, "Number %TO - its %s in base %d\n", "3A", 12, "3A", 12);
    printf("%d\n", l);
    l = overfprintf(stdout, "Int number %d in bytes: %mi\n", 26, 26);
    printf("%d\n", l);
    l = overfprintf(stdout, "Unsigned int number %ud in bytes: %mu\n", 32, 32);
    printf("%d\n", l);
    l = overfprintf(stdout, "Double number %f in bytes: %md\n", 5.22, 5.22);
    printf("%d\n", l);
    l = overfprintf(stdout, "Float number %f in bytes: %mf\n", 6.00001, 6.00001);
    printf("%d\n", l);

    printf("\n--- oversprintf ---\n");
    l = oversprintf("Number %d in Roman numerals: %Ro\n", -45, -45);
    printf("%d\n", l);
    l = oversprintf("Number %u in Zeckendorf representation: %Zr\n", 100, 100);
    printf("%d\n", l);
    l = oversprintf("Number %d in base %d: %Cv\n", -67, 14, -67, 14);
    printf("%d\n", l);
    l = oversprintf("Number %d in base %d: %CV\n", -67, 14, -67, 14);
    printf("%d\n", l);
    l = oversprintf("Number %to - its %s in base %d\n", "-3a", 12, "-3a", 12);
    printf("%d\n", l);
    l = oversprintf("Number %TO - its %s in base %d\n", "-3A", 12, "-3A", 12);
    printf("%d\n", l);
    l = oversprintf("Int number %d in bytes: %mi\n", 26, 26);
    printf("%d\n", l);
    l = oversprintf("Unsigned int number %ud in bytes: %mu\n", 32, 32);
    printf("%d\n", l);
    l = oversprintf("Double number %f in bytes: %md\n", 5.22, 5.22);
    printf("%d\n", l);
    l = oversprintf("Float number %f in bytes: %mf\n", 6.00001, 6.00001);
    printf("%d\n", l);
}