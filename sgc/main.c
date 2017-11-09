#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "requires.h"
#include "y.tab.h"
#include "symboltable.h"
#include "ast.h"
#include "generator.h"
#include "code.h"
#include "error.h"

int testsymboltable(void);
void test_array(void);
void usage(void);

int main(int argc, char *argv[]) {
    extern FILE *yyin;
    extern char *infile;
    FILE *yyout;
    char *outfile;
    int out = 0;
    int debug = 0;
    
    if (argc < 2) {
        usage();
        return 0;
    }
    else {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "-h")) {
                usage();
                return 0;
            }
            
            else if (!strcmp(argv[i], "-d"))
                debug = 1;
            
            else if (!strcmp(argv[i], "-o")) {
                //yyout = fopen(argv[i+1], "w");
                outfile = argv[i+1];
                out = 1;
                i++;
            }
            else {
                if ((yyin = fopen(argv[i], "r")) == NULL) {
                    fprintf(stderr, "sgc: ERROR: no such file or directory %s\n", argv[i]);
                }
                infile = argv[i];
            }
        }
    }

    if (!yyin) {
        fprintf(stderr, "sgc: ERROR: no input file\n");
        return -1;
    }

    yylineno = 0;
    // syntax error
    if (yyparse()) {
        return -1;
    }
    // parsing successful
    else {        
        code_gen(root);
                
        if (debug) {
            disp_table(symboltable);
            disp_code(&code);
        }
        else {            
            if (!out)
                yyout = fopen("a.gstal", "w");
            else
                yyout = fopen(outfile, "w");
            
            write_code(yyout, &code);

            fclose(yyout);
            fclose(yyin);
        }
    }    
       
    return 0;
}

void usage() {
    printf("sgc - slic to gstal compiler\n");
    printf("Usage: sgc [options] file\n");
    printf("Options:\n");
    printf("%s-h%-12sDisplay this information\n", "  ", " ");
    printf("%s-d%-12sPrint symbol table and gstal to stdout\n", "  ", " ");
    printf("%s-o <file>%-5sPlace gstal output in <file>\n", "  ", " ");
    printf("\nSee README for more information\n\n");
}

void test_array() {
    Array t;
    init_code(&t, 128);

    for (int i = 0; i < 11; i++) {
        add_code(&t, "instruction");
    }

    disp_code(&t);

    insert_code(&t, "HERE", 5);
}

int testsymboltable() {
    char name[255];
    int dt;
    int type;
    int addr;
    int size;
    
    symbol *s;

    printf("input 4 symbols\n");
    for (int i = 0; i < 4; i++) {
        printf("symbol %d\n", i);
        scanf("%s", name);
        scanf("%d", &dt);
        scanf("%d", &type);
        scanf("%d", &addr);
        scanf("%d", &size);
        s = (symbol *) malloc(sizeof(symbol));
        *s = make_symbol(name, dt, type, addr, size);
        int i = insert_symbol(symboltable, s);
        printf("insert returned %d\n", i);
    }
    disp_table(symboltable);

    printf("Search for a symbol: ");
    scanf("%s", name);

    s = (symbol *) malloc(sizeof(symbol));
    s = search(name);
    if (s != NULL)
        disp_symbol(*s);
    else
        printf("NOT FOUND!\n");
    
    return 0;
}
