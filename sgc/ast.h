#ifndef AST_H_
#define AST_H_

#include "symboltable.h"

typedef struct ast {
    int nodetype;

    struct ast *next;
    struct ast *l;
    struct ast *r;
    struct ast *unary;

    int n;
    float f;
    char *str;
    
    symbol *s;
    
} ast;

ast *root;

ast* new_ast(int nodetype);
ast* new_int(int val);
ast* new_float(float val);
ast* new_string(char *str);
ast* new_var(symbol *s);
void free_ast(ast *a);

#endif
