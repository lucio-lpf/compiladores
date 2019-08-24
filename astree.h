#include "hash.h"

#ifndef ASTREE_HEADER
#define ASTREE_HEADER

#define MAX_SONS 4

#define AST_SYMBOL 0
#define AST_LE 1
#define AST_GE 2
#define AST_NE 3
#define AST_EQ 4
#define AST_AND 5
#define AST_OR 6
#define AST_LESS 7
#define AST_GREATER 8
#define AST_NEG 9
#define AST_MULT 10
#define AST_ADD 11
#define AST_SUB 12
#define AST_DIV 13
#define AST_DECLARACAO 14
#define AST_FUNC 15
#define AST_VAR 16
#define AST_VECTOR_EMPTY 17
#define AST_VECTOR 18
#define AST_CMDLIST 19
#define AST_READ 20
#define AST_PRINT 21
#define AST_RETURN 22
#define AST_BLOCO 23
#define AST_BYTE 24
#define AST_SHORT 25
#define AST_LONG 26
#define AST_FLOAT 27
#define AST_DOUBLE 28
#define AST_WHEN 29
#define AST_ELSE 30
#define AST_WHILE 31
#define AST_FOR 32
#define AST_VALORLIST 33
#define AST_DEF 34
#define AST_PARAMLIST 35
#define AST_VAR_INIT 36
#define AST_VECTOR_INIT 37
#define AST_ARG 38
#define AST_FUNC_PARAM 39
#define AST_FUNC_EMPTY 40
#define AST_EXPR_VECTOR 41
#define AST_EXPR 42
#define AST_EXPR_FUNC 43
#define AST_EXPR_FUNC_EMPTY 44




typedef struct s_astree
	{
	int verif;
	int type;
	HASH_NODE * symbol;
	struct s_astree * son[MAX_SONS]; 
	} ASTREE;

ASTREE* astreeCreate(int type, HASH_NODE *symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);
void astreePrint(ASTREE *node);
FILE *FileTree;
void nodeType(ASTREE *node);

#endif