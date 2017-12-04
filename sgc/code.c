/*
*  Thais Minet
*  CS 4223
*  code.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "requires.h"
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

void replace_code(Array *code, char *instr, size_t index) {
    if (code->used == code->size) {
        code->size *= 2;
        code->array = (char **) realloc(code->array, code->size * sizeof(char *)*50);
    }

    code->array[index] = instr;
}

void insert_code(Array *code, char *instr, size_t index) {
    if (code->used == code->size) {
        code->size *= 2;
        code->array = (char **) realloc(code->array, code->size * sizeof(char *)*50);
    }
    
    size_t i;
    for (i = code->used; i >= index; i--) {
        code->array[i+1] = code->array[i];        
    }
    code->used++;
    code->array[index] = instr;
}

void disp_code(Array *code) {
    int i;
    fprintf(stderr, "\nCODE:\n");
        
    for (i = 0; i < code->used; i++) {
        if (code->array[i] != NULL) {
            fprintf(stderr, "%d\t%s\n", i, code->array[i]);            
        }
        else {
            fprintf(stderr, "%d\tNULL ; **ERROR** null statement\n", i);
        }
    }    
}

void write_code(FILE *fp, Array *code) {
    int i = 0;
    while (code->array[i] != NULL) {
        if (i == code->used) {
            fprintf(fp, "%s", code->array[i]);
        }
        else {
            fprintf(fp, "%s\n", code->array[i]);
        }              
        i++;
    }
}

void free_code(Array *code) {
    free(code->array);
    code->array = NULL;
    code->used = code->size = 0;
}
