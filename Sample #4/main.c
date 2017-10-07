/*
 * ========================================================================
 * 
 * sample.c ----- In-class example of a main program file to be used in
 *                conjunction with a yacc parser; generates GSTAL code to
 *                evaluate expressions in the parse trees constructed by
 *                the parser.
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#include "y.tab.h"
#include "sample.h"
#include <stdio.h>

void codegen();
void exprgen(struct expression *);


/*
 * ========================================================================
 * main()
 * ========================================================================
 */

int main()
{
   if (yyparse())
      printf("Syntax error\n");
   else
      codegen();
      
   return(0);
}


/*
 * ========================================================================
 * codegen(p) -- Output a GSTAL translation of a "program" that evaluates
 *               constant integer expressions. Write the GSTAL code to
 *               the standard output.
 * ========================================================================
 */

void codegen()
{      
   struct listnode *p;

   p = list;
   while (p != NULL) {
      exprgen(p->exp);
      printf("PTI\nPTL\n");
      p = p->link;
   }
   printf("HLT\n");
   
   return;
}


/*
 * ========================================================================
 * exprgen(p) -- Output GSTAL code to evaluate an integer expression.
 *               p is a pointer to the expression. Write the GSTAL code
 *               to the standard output.
 * ========================================================================
 */

void exprgen(struct expression *p)
{
   if (p->kind == EK_INT) {
      printf("LLI %d\n", p->value);
   }
   else {
      switch (p->operator) {
         case OP_ADD:  exprgen(p->l_operand);
                       exprgen(p->r_operand);
                       printf("ADI\n");
                       break;

         case OP_SUB:  exprgen(p->l_operand);
                       exprgen(p->r_operand);
                       printf("SBI\n");
                       break;

         case OP_MUL:  exprgen(p->l_operand);
                       exprgen(p->r_operand);
                       printf("MLI\n");
                       break;

         case OP_DIV:  exprgen(p->l_operand);
                       exprgen(p->r_operand);
                       printf("DVI\n");
                       break;

         case OP_UMIN: exprgen(p->r_operand);
                       printf("NGI\n");
                       break;
      }
   }
   return;
}
