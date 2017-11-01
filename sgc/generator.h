#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <stdio.h>
#include "y.tab.h"
#include "symboltable.h"
#include "ast.h"
#include "code.h"

extern int addr;

int code_gen(ast *root);
int initialize(void);
int stmt_gen(ast *a);
int assign_gen(ast *a);
int print_gen(ast *a);
int pstring_gen(char *str);
int expr_gen(ast *a);
int mod_gen(ast *a);
int add_int_instr(char *instr, int n);
int add_float_instr(char *instr, float f);
void add_instr(char *instr);
int add_varref(ast *a);

#endif
