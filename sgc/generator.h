#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <stdio.h>
#include "ast.h"

extern int addr;

int code_gen(ast *root);
void initialize(void);
int stmt_gen(ast *a);
void print_gen(ast *a);
void pstring_gen(char *str);
int assign_gen(ast *a);
int read_gen(ast *a);
int add_varref(ast *a);
int expr_gen(ast *a);
int mod_gen(ast *a);

#endif
