/*
* ========================================================================
* 
* Thais Minet
* CS 4223
* main.c
* 
* 
* ========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

#include "symboltable.h"
#include "ast.h"
#include "generator.h"
#include "code.h"

int testsymboltable();
void test_array();

int main() {
    
    if (yyparse())
        printf("Syntax error\n");
    else {
        
        code_gen(root);
    }
    
    return 0;
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
