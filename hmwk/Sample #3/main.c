/*
 * ========================================================================
 * 
 * sample3.c ---- In-class example of a main program file to be used in
 *                conjunction with a yacc parser; evaluates arithmetic
 *                expressions in the parse trees constructed by the 
 *                parser.
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#include "y.tab.h"
#include "sample3.h"
#include <stdio.h>

void run();

main()
{
   if (yyparse())
      printf("Syntax error\n");
   else
      run();
      
   return(0);
}


/*
 * ========================================================================
 * run() -- Evaluate all of the expressions in a "program" and write the
 *          values to the standard output.
 * ========================================================================
 */


void run()
{        
   struct listnode *p;
   
   p = list;
   while (p != NULL) {
      printf("%d\n", eval(p->exp));
      p = p->link;
   }
   
   return;

}


/*
 * ========================================================================
 * eval(p) -- Evaluate an integer expression.  p is a pointer to the 
 *            expression.  Return the resulting int value.
 * ========================================================================
 */

int eval(struct expression *p)
{
   int value;

   if (p->kind == EK_INT) {
      value = p->value;
   }
   else {
      switch (p->operator) {
         case OP_ADD:  value = eval(p->l_operand) + eval(p->r_operand);
                       break;
         case OP_SUB:  value = eval(p->l_operand) - eval(p->r_operand);
                       break;
         case OP_MUL:  value = eval(p->l_operand) * eval(p->r_operand);
                       break;
         case OP_DIV:  value = eval(p->l_operand) / eval(p->r_operand);
                       break;
         case OP_UMIN: value = - eval(p->r_operand);
                       break;
      }
   }
   return (value);
}
