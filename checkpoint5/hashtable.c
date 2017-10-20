#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

int main() {
    /*
    char name[255];
    int dt;
    int type;
    int addr;
    int size;
    
    symbol *s;
    
    for (int i = 0; i < 4; i++) {
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
    
    return 0;
    */
}

int insert_symbol(symbol *symboltable[], symbol *s) {
    int i = 0;
    unsigned long h = hash(s->name, M);
    
    printf("hash = %lu for %s\n", h, s->name);
    printf("--------------------\n");
    
    while (symboltable[(h+i)%M] != NULL) {
        if (!strcmp(symboltable[(h+i)%M]->name, s->name)) return -1;
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
    printf("name = %s\n", s.name);

    if (s.datatype == 0)
        printf("datatype = %s\n", "INTEGER");
    else
        printf("datatype = %s\n", "REAL");
    
    if (s.type == 0)
        printf("type = %s\n", "SCALAR");
    else
        printf("type = %s\n", "ARRAY");
    
    printf("address = %d\n", s.addr);
    printf("size = %d\n", s.size);
}

void disp_table(symbol *symboltable[]) {
    for (int i = 0; i < M; i++) {
        if (symboltable[i] != NULL) {
            printf("--------------------\n");
            printf("POS: %d\n", i);
            disp_symbol(*symboltable[i]);
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
