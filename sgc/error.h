#ifndef ERROR_H_
#define ERROR_H_

char *infile;

void duplicate_variable(char *var);
void undeclared_variable(char *var);
void invalid_array_size(char *var);
void invalid_var_type(char *var, int exptype);
void invalid_var_ref(char *var, int exptype);
void yyerror(char *errmsg);

#endif
