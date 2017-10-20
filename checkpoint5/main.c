/*
* ========================================================================
* 
* Thais Minet
* CS 4223 Checkpoint #5
* main.c
* 
* 
* ========================================================================
*/

#include "y.tab.h"
#include "hashtable.h"
#include <stdio.h>

int main() {
    if (yyparse())
        printf("Syntax error\n");
    else {
        printf("SUCCESS!\n");
    }
    disp_table();

    return 0;
}
