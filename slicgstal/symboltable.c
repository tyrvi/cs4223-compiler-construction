/*
* ========================================================================
* 
* Thais Minet
* CS 4223 Checkpoint #5
* hashtable.c
* 
* ========================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symboltable.h"

int insert(char *name, int datatype, int type, int addr, int size) {
    symbol *s;
    s = (symbol *) malloc(sizeof(symbol));
    *s = make_symbol(name, datatype, type, addr, size);
    
    return insert_symbol(symboltable, s);
}

symbol* search(char *name) {    
    int i = 0;
    unsigned long h = hash(name, M);

    while (symboltable[(h+i)%M] != NULL) {
        if (!strcmp(symboltable[(h+i)%M]->name, name)) {
            return symboltable[(h+i)%M];
        }
        i++;
    }
    
    return (symbol *) NULL;
}

int insert_symbol(symbol *symboltable[], symbol *s) {
    int i = 0;
    unsigned long h = hash(s->name, M);
    
    while (symboltable[(h+i)%M] != NULL) {
        if (!strcmp(symboltable[(h+i)%M]->name, s->name)) return -1; // duplicate variable
        i++;
    }
    symboltable[(h+i)%M] = s;

    return 0;
}

symbol make_symbol(char *name, int datatype, int type, int addr, int size) {
    symbol s;
        
    s.name = strdup(name);
    s.datatype = datatype;
    s.type = type;
    s.addr = addr;
    s.size = size;

    return s;
}

void disp_symbol(symbol s) {

    printf("|%-12s|%-9s|%-6s|%-6d|%-6d|\n", s.name,
           s.datatype == 0 ? "INTEGER" : "REAL",
           s.type == 0 ? "SCALAR" : "ARRAY",
           s.size, s.addr);    
}

void disp_table() {
    printf("+------+------------+---------+------+------+------+\n");
    printf("|Pos   |name        |datatype |type  |size  |addr  |\n");
    printf("+------+------------+---------+------+------+------+\n");
    for (int i = 0; i < M; i++) {
        if (symboltable[i] != NULL) {
            printf("|%-6d", i);
            disp_symbol(*symboltable[i]);
            printf("+------+------------+---------+------+------+------+\n");
        }
    }
}

unsigned long hash(const char *s, unsigned long m) {
    unsigned long h;
    unsigned const char *us;

    // ensure char values >= 0
    us = (unsigned const char *) s;

    h = 0;
    while (*us != '\0') {
        h = (h * BASE + *us) % m;
        us++;
    }

    return h;
}
