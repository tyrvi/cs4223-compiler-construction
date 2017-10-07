/*
 * ========================================================================
 * 
 * sample.h ----- In-class example of a header file to be used in conjunc-
 *                tion with a yacc parser; contains #defines and global
 *                declarations.
 * 
 * Programmer --- Bryan Crawley
 * 
 * ========================================================================
 */

#define EK_OP   0
#define EK_INT  1

#define OP_ADD  0
#define OP_SUB  1
#define OP_MUL  2
#define OP_DIV  3
#define OP_UMIN 4

struct listnode {
   struct listnode *link;
   struct expression *exp;
};

struct expression {
   char kind;
   char operator;
   struct expression *l_operand;
   struct expression *r_operand;
   int value;
};

extern struct listnode *list;
