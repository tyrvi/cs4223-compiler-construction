#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "generator.h"
#include "code.h"

#define ADD_CODE(c, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); add_code(&code, instr); }
#define ADD_UNARY(c) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); add_code(&code, instr); }
#define INSERT_CODE(c, offset, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__), insert_code(&code, instr, offset); }
#define INSERT_UNARY(c) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); add_code(&code, instr); }

int code_gen(ast *root) {    
    initialize();

    ast *a;
    a = root;
    int num_stmts = 0;
    
    while (a != NULL) {        
        num_stmts++;
        stmt_gen(a);
        a = a->next;        
    }

    ADD_UNARY("HLT ; end prgm");
    
    printf("\n# STMTS = %d\n", num_stmts);
    disp_code(&code);
    
    return 0;
}

int initialize() {
    
    disp_table(symboltable);

    int max_addr = -1;
    for (int i = 0; i < M; i++) {
        if (symboltable[i] != NULL) {
            if (symboltable[i]->addr > max_addr)
                max_addr = symboltable[i]->addr;
        }
    }
    
    init_code(&code, 5);
    ADD_CODE("ISP %d", max_addr+1);

    return 0;
}

int stmt_gen(ast *a) {
    if (a == NULL) return -1;
    
    switch (a->nodetype) {
    case PRINT:
        print_gen(a);
        break;
    case ASSIGNMENT:
        assign_gen(a);
        break;
    }
    
    return 0;
}

int print_gen(ast *a) {
    ast *printitem = a->r;

    ADD_UNARY("NOP ; print statement");
    //printf("NOP ; print statement\n");
    while (printitem != NULL) {
        if (printitem->nodetype == STRING) {
            pstring_gen(printitem->str);
        }
        else if (printitem->nodetype == BANG) {
            char bang = '\n';
            ADD_CODE("LLI %d", bang);
            ADD_UNARY("PTC");
        }
        else {
            if (expr_gen(printitem) == REAL_TYPE) {
                ADD_UNARY("PTF");
            }
            else {
                ADD_UNARY("PTI");
            }
        }
            
        printitem = printitem->next;
    }
    
    return 0;    
}

int pstring_gen(char *str) {
    
    for ( ; *str != '\0'; str++) {
        ADD_CODE("LLI %d", *str);
        ADD_UNARY("PTC");
    }

    return 0;
}

int assign_gen(ast *a) {
    ADD_CODE("NOP ; assignment stmt for %s", a->l->s->name);
    ADD_CODE("LRA %d", a->l->s->addr);
    int type = expr_gen(a->r);
    if (type == REAL_TYPE && a->l->s->datatype == INT_TYPE) {
        ADD_UNARY("FTI");
    }
    else if (type == INT_TYPE && a->l->s->datatype == REAL_TYPE) {
        ADD_UNARY("ITF");
    }
    ADD_UNARY("STO");
    
    return 0;
}

int expr_gen(ast *a) {
    int ltype;
    int rtype;
    int type;

    if (a->nodetype == INT_CONST) {
        ADD_CODE("LLI %d", a->n);
        type = INT_TYPE;
    }
    else if (a->nodetype == REAL_CONST){
        ADD_CODE("LLF %f", a->f);
        type = REAL_TYPE;
    }
    else if (a->nodetype == VARIABLE)
        type = add_varref(a->s);
    
    else if (a->nodetype == NOT) {
        type = expr_gen(a->unary);
        ADD_UNARY("NOP ; not operation");
        if (type  == REAL_TYPE) {            
            ADD_CODE("LLF %f", 0.0f);
            ADD_UNARY("EQF");
        }
        else {
            ADD_CODE("LLI %d", 0);
            ADD_UNARY("EQI");
        }
    }
    
    else if (a->nodetype == SUB && a->unary) {
        type = expr_gen(a->unary);
        if (type == REAL_TYPE) {
            ADD_UNARY("NGF");
        }
        else {
            ADD_UNARY("NGI");
        }
    }

    else if (a->nodetype == ADD && a->unary) {
        type = expr_gen(a->unary);     
    }

    else if (a->nodetype == MOD)
        mod_gen(a);    
            
    return type;
}

int mod_gen(ast *a) {
    return 0;
}

int add_varref(symbol *s) {
    ADD_CODE("NOP ; load %s", s->name);
    ADD_CODE("LRA %d", s->addr);
    ADD_UNARY("LOD");

    return s->datatype ? REAL_TYPE : INT_TYPE;    
}
