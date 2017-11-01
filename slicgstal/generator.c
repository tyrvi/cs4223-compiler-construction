#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "generator.h"
#include "code.h"

#define ADD_CODE(c, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); add_code(&code, instr); }
#define ADD_UNARY(c) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); add_code(&code, instr); }
#define INSERT_CODE(c, offset, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); insert_code(&code, instr, offset); }
#define INSERT_UNARY(c, offset) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); insert_code(&code, instr, offset); }

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
    //INSERT_CODE("NOP ; inserted 1st here %s", 1, "offset = 1");
    //INSERT_CODE("NOP ; inserted 2nd here %s", 3, "offset = 3");
    
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
    
    init_code(&code, 128);
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
    int ltype;
    int rtype;
    ADD_CODE("NOP ; assignment stmt for %s", a->l->s->name);
    ltype = add_varref(a->l);
    rtype = expr_gen(a->r);

    if (ltype == INT_TYPE && rtype == REAL_TYPE) {
        ADD_UNARY("FTI");
    }
    else if (ltype == REAL_TYPE && rtype == INT_TYPE) {
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
    else if (a->nodetype == VARIABLE) {
        type = add_varref(a);
        ADD_UNARY("LOD");
    }
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

    else if (a->nodetype == MOD) {
        type = mod_gen(a);
    }

    else {
        ltype = expr_gen(a->l);
        size_t castdepth = code.used + 1;
        rtype = expr_gen(a->r);
        
        size_t offset = code.used - castdepth;
        if (ltype == INT_TYPE && rtype == REAL_TYPE) {
            INSERT_UNARY("ITF ; cast left op", offset);
            //INSERT_CODE("ITF ; cast left operand to real", offset);
            type = REAL_TYPE;
        }
        else if (ltype == REAL_TYPE && rtype == INT_TYPE) {
            ADD_UNARY("ITF ; cast right operand to real");
            type = REAL_TYPE;
        }
        else {
            if (type == REAL_TYPE) {
                switch (a->nodetype) {
                case AND:
                    ADD_UNARY("MLF");
                    break;
                case OR:
                    ADD_UNARY("ADF");
                    break;
                case LT:
                    ADD_UNARY("LTF");
                    break;
                case LTE:
                    ADD_UNARY("LEF");
                    break;
                case GT:
                    ADD_UNARY("GTF");
                    break;
                case GTE:
                    ADD_UNARY("GEF");
                    break;
                case EQ:
                    ADD_UNARY("EQF");
                    break;
                case NEQ:
                    ADD_UNARY("NEF");
                    break;
                case ADD:
                    ADD_UNARY("ADF");
                    break;
                case SUB:
                    ADD_UNARY("SBF");
                    break;
                case MUL:
                    ADD_UNARY("MLF");
                    break;
                case DIV:
                    ADD_UNARY("DVF");
                    break;
                }
            }
            else {
                switch (a->nodetype) {
                case AND:
                    ADD_UNARY("MLF");
                    break;
                case OR:
                    ADD_UNARY("ADF");
                    break;
                case LT:
                    ADD_UNARY("LTF");
                    break;
                case LTE:
                    ADD_UNARY("LEF");
                    break;
                case GT:
                    ADD_UNARY("GTF");
                    break;
                case GTE:
                    ADD_UNARY("GEF");
                    break;
                case EQ:
                    ADD_UNARY("EQF");
                    break;
                case NEQ:
                    ADD_UNARY("NEF");
                    break;
                case ADD:
                    ADD_UNARY("ADF");
                    break;
                case SUB:
                    ADD_UNARY("SBF");
                    break;
                case MUL:
                    ADD_UNARY("MLF");
                    break;
                case DIV:
                    ADD_UNARY("DVF");
                    break;
                }
            }
        }
    }
            
    return type;
}

int mod_gen(ast *a) {
    return 0;
}

int add_varref(ast *a) {
    int type;

    ADD_CODE("NOP ; load %s", a->s->name);
    ADD_CODE("LRA %d", a->s->addr);
    if (a->s->type) {
        type = expr_gen(a->unary);
        if (type == REAL_TYPE) {
            ADD_UNARY("FTI");
        }
        ADD_UNARY("ADI");
    }

    return a->s->datatype ? REAL_TYPE : INT_TYPE;    
}
