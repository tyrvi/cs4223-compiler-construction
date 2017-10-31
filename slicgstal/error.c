#include <stdio.h>

void duplicate_variable(char *var) {
    printf("Error: duplicate variable '%s' on line %d\n", var, 0);
}

void undeclared_variable(char *var) {
    printf("Error: undeclared variable '%s' on line %d\n", var, 0);
}
