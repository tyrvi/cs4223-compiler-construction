#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <stdio.h>
#include "ast.h"

extern int addr;

int begin_code_gen(ast *root);
int code_gen(ast *a);
void initialize(void);
int stmt_gen(ast *a);
int counting_gen(ast *a);
int while_gen(ast *a);
int if_gen(ast *a);
int else_gen(ast *a);
void print_gen(ast *a);
void pstring_gen(char *str);
int assign_gen(ast *a);
int read_gen(ast *a);
int add_varref(ast *a);
int expr_gen(ast *a);
int mod_gen(ast *a);

#endif
