#include "astree.h"
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"


ASTREE* astreeCreate(int type, HASH_NODE *symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3)
{
	ASTREE *newnode = 0;

	newnode = calloc(1,sizeof(ASTREE));
	newnode->type = type;
	newnode->symbol = symbol;
	newnode->son[0] = son0;
	newnode->son[1] = son1;
	newnode->son[2] = son2;
	newnode->son[3] = son3;
	return newnode;
};

void astreePrint(ASTREE *node)
{
	int i=0;
	if(!node)
		return;

	nodeType(node);

	for(i=0; i<MAX_SONS; i++)
		if(node->son[i]) {astreePrint(node->son[i]);}

};

void nodeType(ASTREE *node)
{
	int i = 0;
	if(!node)
		return;
	if(node->verif)
		return;
	else
		node -> verif = 1;

switch(node->type)
	{
		case AST_SYMBOL:
		if (node->symbol)
			if(node->symbol->text)
				fprintf(FileTree, "%s ", node->symbol->text);
 		break;

 		case AST_LE:
			nodeType(node->son[0]);
			fprintf(FileTree,"<= ");
			nodeType(node->son[1]);
		break;

		case AST_GE:
			nodeType(node->son[0]);
			fprintf(FileTree,">= ");
			nodeType(node->son[1]);
		break;

		case AST_NE:
			nodeType(node->son[0]);
			fprintf(FileTree,"!= ");
			nodeType(node->son[1]);
		break;

		case AST_EQ:
			nodeType(node->son[0]);
			fprintf(FileTree,"== ");
			nodeType(node->son[1]);
		break;

		case AST_AND:
			nodeType(node->son[0]);
			fprintf(FileTree,"&& ");
			nodeType(node->son[1]);
		break;

		case AST_OR:
			nodeType(node->son[0]);
			fprintf(FileTree,"|| ");
			nodeType(node->son[1]);
		break;

		case AST_LESS:
			nodeType(node->son[0]);
			fprintf(FileTree,"< ");
			nodeType(node->son[1]);
		break;

		case AST_GREATER:
			nodeType(node->son[0]);
			fprintf(FileTree,"> ");
			nodeType(node->son[1]);
		break;

		case AST_NEG:
			nodeType(node->son[0]);
			fprintf(FileTree,"! ");
		break;

		case AST_MULT:
			nodeType(node->son[0]);
			fprintf(FileTree,"* ");
			nodeType(node->son[1]);
		break;

		case AST_ADD:
		    nodeType(node->son[0]);
			fprintf(FileTree,"+ ");
			nodeType(node->son[1]);
		break;

		case AST_SUB:
			nodeType(node->son[0]);
			fprintf(FileTree,"- ");
			nodeType(node->son[1]);
		break;

		case AST_DIV:
			nodeType(node->son[0]);
			fprintf(FileTree,"/ ");
			nodeType(node->son[1]);
		break;

		case AST_DECLARACAO:
			nodeType(node->son[0]);
			fprintf(FileTree,";\n");
			nodeType(node->son[1]);
		break;

		case AST_FUNC:
			nodeType(node->son[0]);
			fprintf(FileTree,";");
			nodeType(node->son[1]);
		break;

		case AST_VAR:
			nodeType(node->son[0]);
			fprintf(FileTree,": ");
			nodeType(node->son[1]);
			nodeType(node->son[2]);
		break;

		case AST_VECTOR_EMPTY:
			nodeType(node->son[0]);
			fprintf(FileTree,": ");
			nodeType(node->son[1]);
			fprintf(FileTree,"[");
			nodeType(node->son[2]);
			fprintf(FileTree,"]");
		break;

		case AST_VECTOR:
			nodeType(node->son[0]);
			fprintf(FileTree,": ");
			nodeType(node->son[1]);
			fprintf(FileTree,"[");
			nodeType(node->son[2]);
			fprintf(FileTree,"]");
			nodeType(node->son[3]);
		break;

		case AST_CMDLIST:
			nodeType(node->son[0]);
			fprintf(FileTree,";\n");
			nodeType(node->son[1]);
		break;

		case AST_READ:
			fprintf(FileTree,"read ");
			nodeType(node->son[0]);
		break;

		case AST_PRINT:
			fprintf(FileTree,"print ");
			nodeType(node->son[0]);
		break;

		case AST_RETURN:
			fprintf(FileTree,"return ");
			nodeType(node->son[0]);
		break;

		case AST_BLOCO:
			fprintf(FileTree,"{");
			nodeType(node->son[0]);
			fprintf(FileTree,"}");
		break;

		case AST_BYTE:
			fprintf(FileTree,"byte ");
		break;

		case AST_SHORT:
			fprintf(FileTree,"short ");
		break;

		case AST_LONG:
			fprintf(FileTree,"long ");
		break;

		case AST_FLOAT:
			fprintf(FileTree,"float ");
		break;

		case AST_DOUBLE:
			fprintf(FileTree,"double ");
		break;

		case AST_WHEN:
			fprintf(FileTree,"when (");
			nodeType(node->son[0]);
			fprintf(FileTree,") then\n");
			nodeType(node->son[1]);
		break;

		case AST_ELSE:
			fprintf(FileTree,"when (");
			nodeType(node->son[0]);
			fprintf(FileTree,") then\n");
			nodeType(node->son[1]);
			fprintf(FileTree,"else\n");
			nodeType(node->son[2]);
		break;

		case AST_WHILE:
			fprintf(FileTree,"while (");
			nodeType(node->son[0]);
			fprintf(FileTree,")\n");
			nodeType(node->son[1]);
		break;

		case AST_FOR:
			fprintf(FileTree,"for (");
			nodeType(node->son[0]);
			fprintf(FileTree,"= ");
			nodeType(node->son[1]);
			fprintf(FileTree,"to ");
			nodeType(node->son[2]);
			fprintf(FileTree,")\n");
			nodeType(node->son[3]);
		break;

		case AST_VALORLIST:
			nodeType(node->son[0]);
			nodeType(node->son[1]);
		break;

		case AST_DEF:
			nodeType(node->son[0]);
			nodeType(node->son[1]);
		break;

		case AST_PARAMLIST:
		 	nodeType(node->son[0]);
			fprintf(FileTree,", ");
			nodeType(node->son[1]);
		break;

		case AST_VAR_INIT:
			nodeType(node->son[0]);
			fprintf(FileTree,"= ");
			nodeType(node->son[1]);
		break;

		case AST_VECTOR_INIT:
			nodeType(node->son[0]);
			fprintf(FileTree,"# ");
			nodeType(node->son[1]);
			fprintf(FileTree,"= ");
			nodeType(node->son[2]);
		break;

		case AST_ARG:
			nodeType(node->son[0]);
			nodeType(node->son[1]);

			if(node->son[2]){
			fprintf(FileTree,", ");
			nodeType(node->son[2]);}
		break;

		case AST_FUNC_PARAM:
			nodeType(node->son[0]);
			nodeType(node->son[1]);
			fprintf(FileTree,"(");
			nodeType(node->son[2]);
			fprintf(FileTree,")\n");
			nodeType(node->son[3]);
		break;

		case AST_FUNC_EMPTY:
			nodeType(node->son[0]);
			nodeType(node->son[1]);
			fprintf(FileTree,"(");
			fprintf(FileTree,")\n");
			nodeType(node->son[2]);
		break;

		case AST_EXPR_VECTOR:
			nodeType(node->son[0]);
			fprintf(FileTree,"[");
			nodeType(node->son[1]);
			fprintf(FileTree,"]\n");
		break;

		case AST_EXPR:
			fprintf(FileTree,"(");
			nodeType(node->son[0]);
			fprintf(FileTree,")");
		break;

		case AST_EXPR_FUNC:
			nodeType(node->son[0]);
			fprintf(FileTree,"(");
			nodeType(node->son[1]);
			fprintf(FileTree,")\n");
		break;

		case AST_EXPR_FUNC_EMPTY:
			nodeType(node->son[0]);
			fprintf(FileTree,"(");
			fprintf(FileTree,")\n");
		break;
	}
};
