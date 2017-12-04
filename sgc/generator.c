/*
*  Thais Minet
*  CS 4223
*  generator.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "requires.h"
#include "generator.h"
#include "y.tab.h"
#include "symboltable.h"
#include "code.h"
#include "error.h"

#define ADD_CODE(c, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); add_code(&code, instr); }
#define ADD_UNARY(c) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); add_code(&code, instr); }
//#define INSERT_CODE(c, index, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); insert_code(&code, instr, index); }
//#define INSERT_UNARY(c, index) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); insert_code(&code, instr, index); }
#define REPLACE_CODE(c, index, ...) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c, __VA_ARGS__); replace_code(&code, instr, index); }
#define REPLACE_UNARY(c, index) { char *instr = malloc(sizeof(char *)*50); sprintf(instr, c); replace_code(&code, instr, index); }

// tracks synthesized loop variables
int loopcount = 0;

int begin_code_gen(ast *root) {
    ast *a;
    a = root;    

    initialize();

    code_gen(a);

    ADD_UNARY("HLT ; end prgm");

    return 0;
}

void initialize() {    
    insert("_dividend", INT_TYPE, SCALAR, addr, 1);
    insert("_divisor", INT_TYPE, SCALAR, addr+1, 1);
    
    init_code(&code, 512);
    // 2 addresses for mod operands dividend and divisor
    ADD_CODE("ISP %d", addr+3);
}

int code_gen(ast *a) {

    while (a != NULL) {
        stmt_gen(a);
        a = a->next;        
    }    
    
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
    case EXIT:
        ADD_UNARY("HLT ; exit stmt");
        break;
    case READ:
        read_gen(a);
        break;
    case IF:
        if_gen(a);
        break;
    case ELSE:
        else_gen(a);
        break;
    case WHILE:
        while_gen(a);
        break;
    case COUNTING:
        counting_gen(a);        
        break;    
    }

    return 0;
}

int counting_gen(ast *a) {
    // load, evaluate and store counting variable
    ADD_UNARY("NOP ; initialize counting");
    add_varref(a->unary);
    expr_gen(a->l->l);
    ADD_UNARY("STO");

    // load, evaluate and store synthesized loop variable
    char loopname[100];
    sprintf(loopname, "_loop%d", loopcount);
    symbol *s = search(loopname);

    // loop variables were not synthesized correctly
    if (s == NULL) {
        fprintf(stderr, "sgc: ERROR: internal compiler error");
        exit(1);
    }

    loopcount++;

    ADD_CODE("LRA %d ; %s", s->addr, s->name);
    expr_gen(a->l->r);
    ADD_UNARY("STO");

    ADD_UNARY("NOP ; begin counting");

    // load variables and compare
    // store jmp location
    int jmploc = code.used;
    add_varref(a->unary);
    ADD_UNARY("LOD");

    ADD_CODE("LRA %d ; %s", s->addr, s->name);
    ADD_UNARY("LOD");
    // upward loop
    if (a->l->nodetype == UPWARD) {
        ADD_UNARY("LEI");
    }
    // downward loop
    else {
        ADD_UNARY("GEI");
    }

    size_t jpfindex = code.used;
    ADD_UNARY("NOP ; jpf placeholder");
    code_gen(a->r);

    ADD_UNARY("NOP ; increment loop variable");
    // upward loop
    if (a->l->nodetype == UPWARD) {
        add_varref(a->unary);
        add_varref(a->unary);
        ADD_UNARY("LOD");
        ADD_CODE("LLI %d", 1);
        ADD_UNARY("ADI");
        ADD_UNARY("STO");
    }
    // downward loop
    else {
        add_varref(a->unary);
        add_varref(a->unary);
        ADD_UNARY("LOD");
        ADD_CODE("LLI %d", -1);
        ADD_UNARY("ADI");
        ADD_UNARY("STO");
    }
    
    ADD_CODE("JMP %d", jmploc);
    int jpfloc = code.used;
    REPLACE_CODE("JPF %d", jpfindex, jpfloc);
    ADD_UNARY("NOP ; end counting");
    
    return 0;
}

int while_gen(ast *a) {
    ADD_UNARY("NOP ; begin while");
    int jmploc = code.used;
    int type = expr_gen(a->unary);

    // convert to boolean value
    if (type == REAL_CONST) {        
        ADD_CODE("LLF %f", 0.0f);
        ADD_UNARY("NEF");
    }
    else {
        ADD_CODE("LLI %d", 0);
        ADD_UNARY("NEI");
    }
    
    size_t jpfindex = code.used;
    ADD_UNARY("NOP ; jpf placeholder");
    code_gen(a->l);
    ADD_CODE("JMP %d", jmploc);
    int jpfloc = code.used;
    REPLACE_CODE("JPF %d", jpfindex, jpfloc);
    ADD_UNARY("NOP ; end while");

    return 0;
}

int else_gen(ast *a) {
    ADD_UNARY("NOP ; begin if/else");
    int type = expr_gen(a->unary);

    // convert to boolean value
    if (type == REAL_CONST) {        
        ADD_CODE("LLF %f", 0.0f);
        ADD_UNARY("NEF");
    }
    else {
        ADD_CODE("LLI %d", 0);
        ADD_UNARY("NEI");
    }

    // if
    size_t jpfindex = code.used;
    ADD_UNARY("NOP ; jpf placeholder");
    code_gen(a->l);
    ADD_UNARY("NOP ; jmp placeholder")
    int jpfloc = code.used + 1;
    REPLACE_CODE("JPF %d", jpfindex, jpfloc);

    // else
    size_t jmpindex = code.used-1;
    code_gen(a->r);
    int jmploc = code.used;
    REPLACE_CODE("JMP %d", jmpindex, jmploc);
    ADD_UNARY("NOP ; end if/else");

    return 0;    
}

int if_gen(ast *a) {
    ADD_UNARY("NOP ; begin if stmt");
    int type = expr_gen(a->unary);
    
    if (type == REAL_CONST) {        
        ADD_CODE("LLF %f", 0.0f);
        ADD_UNARY("NEF");
    }
    else {
        ADD_CODE("LLI %d", 0);
        ADD_UNARY("NEI");
    }
    
    size_t jpfindex = code.used;
    ADD_UNARY("NOP ; jpf placeholder");
    code_gen(a->l);
    int jpfloc = code.used;
    REPLACE_CODE("JPF %d", jpfindex, jpfloc);
    ADD_UNARY("NOP ; end if stmt");

    return 0;
}

int read_gen(ast *a) {
    int type = add_varref(a->unary);
    if (type == INT_CONST) {
        ADD_UNARY("INI ; read stmt");
    }
    else {
        ADD_UNARY("INF ; read stmt");
    }

    ADD_UNARY("STO");

    return type;
}

int assign_gen(ast *a) {
    ADD_CODE("NOP ; assignment stmt %s", a->l->s->name);
    int type;
    int ltype = add_varref(a->l);
    int rtype = expr_gen(a->r);

    // casting
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
    int type;
    ADD_CODE("LRA %d ; %s", a->s->addr, a->s->name);

    if (a->s->type == ARRAY) {
        type = expr_gen(a->unary);
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
    else if (a->nodetype == NOT) {
        ADD_UNARY("NOP ; begin not");
        type = expr_gen(a->unary);

        // convert to boolean value
        if (type  == REAL_CONST) {            
            ADD_CODE("LLF %f", 0.0f);
            ADD_UNARY("EQF");
        }
        else {
            ADD_CODE("LLI %d", 0);
            ADD_UNARY("EQI");
        }
        
        ADD_UNARY("NOP ; end not");
        
        return INT_CONST;
    }    
    else if (a->nodetype == SUB && a->unary) {
        ADD_UNARY("NOP ; begin unary -");
        type = expr_gen(a->unary);

        if (type == REAL_CONST) {
            ADD_UNARY("NGF");
        }
        else {
            ADD_UNARY("NGI");
        }
        
        ADD_UNARY("NOP ; end unary -");
        
        return type;
    }    
    else if (a->nodetype == ADD && a->unary) {
        ADD_UNARY("NOP ; unary +");
        type = expr_gen(a->unary);

        return type;
    }
    else if (a->nodetype == MOD) {
        return mod_gen(a);
    }    
    else if (a->nodetype == AND) {
        int ltype = expr_gen(a->l);
        
        ADD_UNARY("NOP ; begin and");
        // convert to boolean value
        if (ltype == REAL_CONST) {
            ADD_CODE("LLF %f", 0.0f);
            ADD_UNARY("NEF");
        }
        else {
            ADD_CODE("LLI %d", 0);
            ADD_UNARY("NEI");
        }
        
        int rtype = expr_gen(a->r);
        // convert to boolean value
        if (rtype == REAL_CONST) {
            ADD_CODE("LLF %f", 0.0f);
            ADD_UNARY("NEF");
        }
        else {
            ADD_CODE("LLI %d", 0);
            ADD_UNARY("NEI");
        }

        ADD_UNARY("MLI");
        ADD_CODE("LLI %d", 0);
        ADD_UNARY("NEI");
        ADD_UNARY("NOP ; end and");
        
        return INT_CONST;            
    }
    else if (a->nodetype == OR) {
        ADD_UNARY("NOP ; begin or");
        int ltype = expr_gen(a->l);

        // convert to boolean value
        if (ltype == REAL_CONST) {
            ADD_CODE("LLF %f", 0.0f);
            ADD_UNARY("NEF");
        }
        else {
            ADD_CODE("LLI %d", 0);
            ADD_UNARY("NEI");
        }
        
        int rtype = expr_gen(a->r);
        // convert to boolean value
        if (rtype == REAL_CONST) {
            ADD_CODE("LLF %f", 0.0f);
            ADD_UNARY("NEF");
        }
        else {
            ADD_CODE("LLI %d", 0);
            ADD_UNARY("NEI");
        }

        ADD_UNARY("ADI");
        ADD_CODE("LLI %d", 0);
        ADD_UNARY("NEI");
        ADD_UNARY("NOP ; end and");

        return INT_CONST;            
    }    
    else {
        int ltype = expr_gen(a->l);
        size_t castindex = code.used;
        ADD_UNARY("NOP ; replacement position"); // insertion placeholder
        int rtype = expr_gen(a->r);
        
        type = INT_TYPE;
        if (ltype == INT_CONST && rtype == REAL_CONST) {            
            REPLACE_UNARY("ITF ; cast left op to real", castindex);
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
            
    return UNKOWN_TYPE;
}

int mod_gen(ast *a) {
    symbol *dividend = search("_dividend");
    symbol *divisor = search("_divisor");

    ADD_UNARY("NOP ; a mod b = a a b / b * -");
    
    int ltype = expr_gen(a->l);
    
    if (ltype == REAL_CONST)
        ADD_UNARY("FTI");        
    
    // load a twice
    ADD_CODE("LAA %d", dividend->addr);
    ADD_UNARY("STM");
    ADD_UNARY("LOD");
    ADD_CODE("LAA %d", dividend->addr);
    ADD_UNARY("LOD");

    int rtype = expr_gen(a->r);
    
    if (rtype == REAL_CONST)
        ADD_UNARY("FTI");    

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
        if (*str == '"')
            str++;
        
        ADD_CODE("LLI %d", *str);
        ADD_UNARY("PTC");
    }
}
