
%{

#include "hash.c"
#include "astree.c"
#include <stdlib.h>
#include "y.tab.h"
#include "symbols.h"


void yyerror(char *);

int running = 1;
int lineNumber = 1;
int tok = 0;
%}


%x COMMENT


%%

"for"		  { return KW_FOR; }
"to"		  { return KW_TO; }
"byte"		{ return KW_BYTE; }
"short"		{ return KW_SHORT; }
"long"		{ return KW_LONG; }
"float"		{ return KW_FLOAT; }
"double"	{ return KW_DOUBLE; }
"when"		{ return KW_WHEN; }
"then"		{ return KW_THEN; }
"else"		{ return KW_ELSE; }
"while"		{ return KW_WHILE; }
"read"		{ return KW_READ; }
"return"	{ return KW_RETURN;}
"print"		{ return KW_PRINT; }


"<="		{ return OPERATOR_LE; }
">="		{ return OPERATOR_GE; }
"=="		{ return OPERATOR_EQ; }
"!="		{ return OPERATOR_NE; }
"&&"		{ return OPERATOR_AND; }
"||"		{ return OPERATOR_OR; }

[0-9]+"."[0-9]+ { yylval.symbol = hashInsert(LIT_REAL, yytext); return LIT_REAL; }
[0-9]+		{ yylval.symbol = hashInsert(LIT_INTEGER, yytext); return LIT_INTEGER; }
\"[^"]*\"	{ yylval.symbol = hashInsert(LIT_STRING, yytext); return LIT_STRING; }
\'.\' { yylval.symbol = hashInsert(LIT_CHAR, yytext); return LIT_CHAR;  }

[a-zA-Z_][a-zA-Z_0-9]*	{ yylval.symbol = hashInsert(TK_IDENTIFIER, yytext) ; printf("ID: %s\n",yytext);return TK_IDENTIFIER;}


[\t]
[ ]
\n		{ ++lineNumber; }
"//".*
"/*"		{ BEGIN(COMMENT); }
[,;:(){}\[\]+*/<>=!$&#]		{ return yytext[0]; }
"-" { return yytext[0]; }

.		{ return TOKEN_ERROR; }

<COMMENT>"*/"	{ BEGIN(INITIAL); }
<COMMENT>.
<COMMENT>\n	{ ++lineNumber; }


%%



int yywrap()
{
  running = 0;
	return 1;
}

int getLineNumber(void)
{
	return lineNumber;
}

int isRunning(void)
{
	return running;
}

#include"y.tab.c"
#include"main.c"
