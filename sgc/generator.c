#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "generator.h"
#include "y.tab.h"
#include "symboltable.h"
#include "code.h"


#define ADD_CODE(c, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); add_code(&code, instr); }
#define ADD_UNARY(c) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); add_code(&code, instr); }
#define INSERT_CODE(c, offset, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); insert_code(&code, instr, offset); }
#define INSERT_UNARY(c, offset) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); insert_code(&code, instr, offset); }

int code_gen(ast *root) {    
    ast *a;
    a = root;
    int num_stmts = 0;

    initialize();

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

void initialize() {
    int max_addr = -1;

    for (int i = 0; i < M; i++) {
        if (symboltable[i] != NULL) {
            if (symboltable[i]->addr > max_addr)
                max_addr = symboltable[i]->addr;
        }
    }

    insert("_dividend", INT_TYPE, SCALAR, max_addr+1, 1);
    insert("_divisor", INT_TYPE, SCALAR, max_addr+2, 1);
    disp_table(symboltable);
    
    init_code(&code, 128);
    // 2 addresses for mod operands dividend and divisor
    ADD_CODE("ISP %d", max_addr+3);
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

int assign_gen(ast *a) {
    ADD_CODE("NOP ; assignment stmt %s", a->l->s->name);
    int type;
    int ltype = add_varref(a->l);
    int rtype = expr_gen(a->r);

    if (ltype == INT_CONST && rtype == REAL_CONST) {
        type = INT_CONST;
        ADD_UNARY("FTI");
    }
    else if (ltype == REAL_CONST && rtype == INT_CONST) {
        type = REAL_CONST;
        ADD_UNARY("ITF");
    }
    ADD_UNARY("STO");

    return type;
}

int add_varref(ast *a) {
    ADD_CODE("LRA %d ; %s", a->s->addr, a->s->name);

    if (a->s->type == ARRAY) {
        int type = expr_gen(a->unary);
        if (type == REAL_CONST) {
            ADD_UNARY("FTI");
        }
        
        ADD_UNARY("ADI");
    }

    if (a->s->datatype == INT_TYPE) return INT_CONST;
    else return REAL_CONST;
}

int expr_gen(ast *a) {
    int type;

    if (a->nodetype == INT_CONST) {
        ADD_CODE("LLI %d", a->n);
        
        return INT_CONST;
    }
    else if (a->nodetype == REAL_CONST){
        ADD_CODE("LLF %f", a->f);
        
        return REAL_CONST;
    }
    else if (a->nodetype == VARIABLE) {
        type = add_varref(a);
        ADD_UNARY("LOD");
        
        return type;
    }
    else if (a->unary) {
        type = expr_gen(a->unary);

        if (a->nodetype == NOT) {
            ADD_UNARY("NOP ; not operation");
            if (type  == REAL_CONST) {            
                ADD_CODE("LLF %f", 0.0f);
                ADD_UNARY("EQF");
            }
            else {
                ADD_CODE("LLI %d", 0);
                ADD_UNARY("EQI");
            }   
        }
        else if (a->nodetype == SUB) {
            if (type == REAL_CONST) {
                ADD_UNARY("NGF");
            }
            else {
                ADD_UNARY("NGI");
            }
        }
        else if (a->nodetype == ADD) {
            ADD_UNARY("NOP ; unary +");
        }

        return type;
    }    

    else if (a->nodetype == MOD) {
        return mod_gen(a);
    }

    else {
        int ltype = expr_gen(a->l);
        size_t castindex = code.used;
        int rtype = expr_gen(a->r);
        
        type = INT_TYPE;
        if (ltype == INT_CONST && rtype == REAL_CONST) {
            INSERT_UNARY("ITF ; cast left op to real", castindex);
            type = REAL_TYPE;
        }
        else if (ltype == REAL_CONST && rtype == INT_CONST) {
            ADD_UNARY("ITF ; cast right op to real");
            type = REAL_TYPE;
        }
        else if (ltype == REAL_CONST && rtype == REAL_CONST) {
            type = REAL_TYPE;
        }

        if (type == REAL_TYPE) {
            switch (a->nodetype) {
            case AND:
                ADD_UNARY("MLF"); break;
            case OR:
                ADD_UNARY("ADF"); break;
            case LT:
                ADD_UNARY("LTF"); break;
            case LTE:
                ADD_UNARY("LEF"); break;
            case GT:
                ADD_UNARY("GTF"); break;
            case GTE:
                ADD_UNARY("GEF"); break;
            case EQ:
                ADD_UNARY("EQF"); break;
            case NEQ:
                ADD_UNARY("NEF"); break;
            case ADD:                
                ADD_UNARY("ADF"); break;
            case SUB:
                ADD_UNARY("SBF"); break;
            case MUL:
                ADD_UNARY("MLF"); break;
            case DIV:
                ADD_UNARY("DVF"); break;
            }
        }
        else {
            switch (a->nodetype) {
            case AND:
                ADD_UNARY("MLI"); break;
            case OR:
                ADD_UNARY("ADI"); break;
            case LT:
                ADD_UNARY("LTI"); break;
            case LTE:
                ADD_UNARY("LEI"); break;
            case GT:
                ADD_UNARY("GTI"); break;
            case GTE:
                ADD_UNARY("GEI"); break;
            case EQ:
                ADD_UNARY("EQI"); break;
            case NEQ:
                ADD_UNARY("NEI"); break;
            case ADD:
                ADD_UNARY("ADI"); break;
            case SUB:
                ADD_UNARY("SBI"); break;
            case MUL:
                ADD_UNARY("MLI"); break;
            case DIV:
                ADD_UNARY("DVI"); break;
            }
        }

        if (type == REAL_TYPE) return REAL_CONST;
        else return INT_CONST;
    }
            
    return -1;
}

int mod_gen(ast *a) {
    symbol *dividend = search("_dividend");
    symbol *divisor = search("_divisor");

    ADD_UNARY("NOP ; a mod b = a a b / b * -");
    int ltype = expr_gen(a->l);
    if (ltype == REAL_CONST) {
        ADD_UNARY("FTI");
    }

    // load a twice
    ADD_CODE("LAA %d", dividend->addr);
    ADD_UNARY("STM");
    ADD_UNARY("LOD");
    ADD_CODE("LAA %d", dividend->addr);
    ADD_UNARY("LOD");

    int rtype = expr_gen(a->r);
    if (rtype == REAL_CONST) {
        ADD_UNARY("FTI");
    }

    // load b
    ADD_CODE("LAA %d", divisor->addr);
    ADD_UNARY("STM");
    ADD_UNARY("LOD");
    ADD_UNARY("DVI");
    ADD_CODE("LAA %d", divisor->addr);
    ADD_UNARY("LOD");
    ADD_UNARY("MLI");
    ADD_UNARY("SBI");
    ADD_UNARY("NOP ; mod end");
        
    return INT_CONST;
}

void print_gen(ast *a) {
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
            if (expr_gen(printitem) == REAL_CONST) {
                ADD_UNARY("PTF");
            }
            else {
                ADD_UNARY("PTI");
            }
        }
            
        printitem = printitem->next;
    }
}

void pstring_gen(char *str) {    
    for ( ; *str != '\0'; str++) {
        ADD_CODE("LLI %d", *str);
        ADD_UNARY("PTC");
    }
}
