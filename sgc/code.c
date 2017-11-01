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
    printf("\nCODE:\n");
    
    while (code->array[i] != NULL) {
        if (i == code->used) {
            printf("%s", code->array[i]);
        }
        else {
            printf("%s\n", code->array[i]);
        }              
        i++;
    }
    
    /*
    for (i = 0; i < code->used; i++) {
        if (code->array[i] != NULL) {
            printf("%d\t%s\n", i, code->array[i]);            
        }
        else {
            printf("%d\tNULL ; **ERROR** null statement\n", i);
        }
    }
    */
}

void free_code(Array *code) {
    free(code->array);
    code->array = NULL;
    code->used = code->size = 0;
}
