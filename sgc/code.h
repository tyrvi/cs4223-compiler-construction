#ifndef CODE_H_
#define CODE_H_

typedef struct Array {
    char **array;
    size_t used;
    size_t size;
} Array;

Array code;

void init_code(Array *code, int initsize);
void add_code(Array *code, char *instr);
void replace_code(Array *code, char *instr, size_t index);
void insert_code(Array *code, char *instr, size_t index);
void disp_code(Array *code);
void write_code(FILE *fp, Array *code);
void free_code(Array *code);

#endif
