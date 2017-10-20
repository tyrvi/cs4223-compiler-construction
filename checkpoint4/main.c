/*
* ========================================================================
* 
* Thais Minet
* CS 4223 Checkpoint #4
* main.c
* 10/3/17
* 
* ========================================================================
*/

#include "y.tab.h"
#include <stdio.h>

int main() {
    if (yyparse())
        printf("Syntax error\n");
    else
        printf("SUCCESS!\n");

    return 0;
}
