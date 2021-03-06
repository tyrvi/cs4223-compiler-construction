/*
*  Thais Minet
*  CS 4223
*  main.c
*/

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
    int in = 0;
    int out = 0;
    int debug = 0;    
    
    if (argc < 2) {
        usage();
        exit(0);
    }
    else {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "-h")) {
                usage();
                exit(0);
            }
            
            else if (!strcmp(argv[i], "-d"))
                debug = 1;
            
            else if (!strcmp(argv[i], "-o")) {
                outfile = argv[i+1];
                out = 1;
                i++;
            }
            
            else {
                if ((yyin = fopen(argv[i], "r")) == NULL) {
                    fprintf(stderr, "sgc: ERROR: no such file or directory %s\n", argv[i]);
                    exit(1);
                }
                in = 1;
                infile = argv[i];
            }
        }
    }

    if (!in) {
        fprintf(stderr, "sgc: ERROR: no input file\n");
        exit(1);
    }

    yylineno = 0;
    
    // parsing successful
    if (!yyparse()) {
        begin_code_gen(root);
                
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

        
        free_code(&code);
        free_ast(root);
        
        exit(0);
    }
    // parsing failed
    else {
        if (root)
            free_ast(root);
        
        exit(1);
    }
       
    return 0;
}

void usage() {
    printf("sgc - slic to gstal compiler\n");
    printf("Usage: sgc [options] infile\n");
    printf("Options:\n");
    printf("%s-h%-12sDisplay this information\n", "  ", " ");
    printf("%s-d%-12sPrint symbol table and gstal to stdout\n", "  ", " ");
    printf("%s-o <outfile>%-5sWrites gstal output to <outfile>\n", "  ", " ");
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
