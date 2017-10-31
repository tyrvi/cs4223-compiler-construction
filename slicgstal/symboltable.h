#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#define BASE (64) // hash base should be larger than number symbols allowed in a variable
#define M (1031) // hash value

#define INT_TYPE 0
#define REAL_TYPE 1

// symbol struct in the symbol table
typedef struct symbol {
    char *name;
    int datatype; // 0 = integer, 1 = real
    int type; // 0 = scalar, 1 = array
    int addr;
    int size; // scalar = 1, array >= 1    
} symbol;

symbol *symboltable[M];

// function declarations
symbol* search(char *name);
int insert(char *name, int datatype, int type, int addr, int size);
unsigned long hash(const char *s, unsigned long m);
symbol make_symbol(char *name, int datatype, int type, int addr, int size);
int insert_symbol(symbol *symboltable[], symbol *s);
void disp_symbol(symbol s);
void disp_table();

#endif
