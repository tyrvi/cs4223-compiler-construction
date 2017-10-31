#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
#include "code.h"
#include "symboltable.h"

void init_code(Array *code, int initsize) {
    code->array = (char **) malloc(initsize * sizeof(char *)*50);
    code->used = 0;
    code->size = initsize;
}

void add_code(Array *code, char *instr) {
    if (code->used == code->size) {
        code->size *= 2;
        code->array = (char **) realloc(code->array, code->size * sizeof(char *)*50);
    }
    
    code->array[code->used++] = instr;
}

void insert_code(Array *code, char *instr, int offset) {
    return;
}

void disp_code(Array *code) {
    int i;
    printf("\nCODE:\n");
    while (code->array[i] != NULL) {
        printf("%s\n", code->array[i]);
        i++;
    }
}

void free_code(Array *code) {
    free(code->array);
    code->array = NULL;
    code->used = code->size = 0;
}
