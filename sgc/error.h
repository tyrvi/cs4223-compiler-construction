#ifndef ERROR_H_
#define ERROR_H_

char *infile;

void duplicate_variable(char *var);
void undeclared_variable(char *var);
void invalid_array_size(char *var);
void yyerror(char *errmsg);

#endif
