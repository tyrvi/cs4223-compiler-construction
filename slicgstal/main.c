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

int testsymboltable();

int main() {
    
    if (yyparse())
        printf("Syntax error\n");
    else {
        
        code_gen(root);
    }
    
    //testsymboltable();
    return 0;
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
