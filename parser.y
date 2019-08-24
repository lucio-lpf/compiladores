%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"

%}

%union
{
  struct hash_struct *symbol;
  struct s_astree *astree;
}


%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_WHEN
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_RETURN
%token KW_PRINT
%token KW_IF
%token KW_TO

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token<symbol> LIT_INTEGER
%token<symbol> LIT_REAL
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING
%token<symbol> TK_IDENTIFIER



%left OPERATOR_AND OPERATOR_OR
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '<' '>' 
%left '-' '+'
%left '*' '/'
%right '!'

%token TOKEN_ERROR

%type <astree> program
%type <astree> global
%type <astree> cmdlist
%type <astree> bloco
%type <astree> cmd
%type <astree> cmd_atr
%type <astree> def
%type <astree> deflist
%type <astree> contr_fluxo
%type <astree> paramlist
%type <astree> paramchama
%type <astree> var
%type <astree> vector
%type <astree> valorlist
%type <astree> name
%type <astree> valor
%type <astree> tipo
%type <astree> tamanho
%type <astree> func
%type <astree> expr


%%

program: 
  global			{$$ = $1; astreePrint($1);}
  ;

global: 
  var ';' global	{$$ = astreeCreate(AST_DECLARACAO, 0, $1, $3, 0, 0);}
  | vector ';' global  {$$ = astreeCreate(AST_DECLARACAO, 0, $1, $3, 0, 0);} 
  | func ';' global {$$ = astreeCreate(AST_FUNC, 0, $1, $3, 0, 0);}
  | {$$ = 0;}
  ;

cmdlist: 
  cmd ';' cmdlist {$$ = astreeCreate(AST_CMDLIST, 0, $1, $3, 0, 0);}
  | {$$ = 0;}
  ;

cmd : 
  cmd_atr {$$ = $1;}
  | contr_fluxo {$$ = $1;}
  | bloco {$$ = $1;}
  | KW_READ name {$$ = astreeCreate(AST_READ, 0, $2, 0, 0, 0);}
  | KW_PRINT def {$$ = astreeCreate(AST_PRINT, 0, $2, 0, 0, 0);} 
  | KW_RETURN expr {$$ = astreeCreate(AST_RETURN, 0, $2, 0, 0, 0);}
  | {$$ = 0;}
  ;

cmd_atr:
  name '=' expr {$$ = astreeCreate(AST_VAR_INIT, 0, $1, $3, 0, 0);}
  | name '#' expr '=' expr  {$$ = astreeCreate(AST_VECTOR_INIT, 0, $1, $3, $5, 0);} 
  ;

bloco: 
  '{' cmdlist '}' {$$ = astreeCreate(AST_BLOCO, 0, $2, 0, 0, 0);}
  ;

vector: 
  name ':' tipo '[' tamanho ']' {$$ = astreeCreate(AST_VECTOR_EMPTY, 0, $1, $3, $5, 0);} 
  | name ':' tipo '[' tamanho ']' valorlist {$$ = astreeCreate(AST_VECTOR, 0, $1, $3, $5, $7);}
  ;

name: 
  TK_IDENTIFIER {$$ = astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
  ;

tipo: 
  KW_BYTE {$$ = astreeCreate(AST_BYTE, 0, 0, 0, 0, 0);}
  | KW_SHORT {$$ = astreeCreate(AST_SHORT, 0, 0, 0, 0, 0);}
  | KW_LONG {$$ = astreeCreate(AST_LONG, 0, 0, 0, 0, 0);}
  | KW_FLOAT {$$ = astreeCreate(AST_FLOAT, 0, 0, 0, 0, 0);}
  | KW_DOUBLE {$$ = astreeCreate(AST_DOUBLE, 0, 0, 0, 0, 0);}
  ;

valor: 
  LIT_INTEGER {$$ = astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
  | LIT_REAL {$$ = astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
  | LIT_CHAR {$$ = astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
  ;

tamanho: 
  LIT_INTEGER {$$ = astreeCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
  ;

valorlist: 
  valor valorlist {$$ = astreeCreate(AST_VALORLIST, 0, $1, $2, 0, 0);}
  | valor {$$ = $1;}
  ;

var: 
  name ':' tipo valor {$$ = astreeCreate(AST_VAR, 0, $1, $3, $4, 0);}
  ; 

def: 
  deflist def {$$ = astreeCreate(AST_DEF, 0, $1, $2, 0, 0);}
  | deflist {$$ = $1;}
  ;

deflist: 
  LIT_STRING {$$ = astreeCreate(AST_SYMBOL, $1, 0, 0 , 0, 0);}
  | expr {$$ = $1;}
  ;

contr_fluxo: 
  KW_WHEN '(' expr ')' KW_THEN cmd {$$ = astreeCreate(AST_WHEN, 0, $3, $6, 0, 0);}
  | KW_WHEN '(' expr ')' KW_THEN cmd KW_ELSE cmd {$$ = astreeCreate(AST_ELSE, 0, $3, $6, $8, 0);}
  | KW_WHILE '(' expr ')' cmd {$$ = astreeCreate(AST_WHILE, 0, $3, $5, 0, 0);}
  | KW_FOR '(' name '=' expr KW_TO expr ')' cmd {$$ = astreeCreate(AST_FOR, 0, $3, $5, $7, $9);}
  ;

paramlist: 
  expr ',' paramlist {$$ = astreeCreate(AST_PARAMLIST, 0, $1, $3, 0, 0);}
  | expr {$$ = $1;}
  ;
  
paramchama: 
  tipo name ',' paramchama {$$ = astreeCreate(AST_ARG, 0, $1, $2, $4, 0);}
  | tipo name {$$ = astreeCreate(AST_ARG, 0, $1, $2, 0, 0);}
  ;

func: 
  tipo name '(' ')' cmd {$$ = astreeCreate(AST_FUNC_EMPTY, 0, $1, $2, $5, 0);}
  | tipo name '(' paramchama ')' cmd {$$ = astreeCreate(AST_FUNC_PARAM, 0, $1, $2, $4, $6);}
  ;


expr:     
    name {$$ = $1;}
    | valor {$$ = $1;}
    | name '[' expr ']' {$$ = astreeCreate(AST_EXPR_VECTOR, 0, $1, $3, 0, 0);}
    | name '(' paramlist ')' {$$ = astreeCreate(AST_EXPR_FUNC, 0, $1, $3, 0, 0);}
    | '(' expr ')' {$$ = astreeCreate(AST_EXPR, 0, $2, 0 , 0, 0);}
    | name '(' ')' {$$ = astreeCreate(AST_EXPR_FUNC_EMPTY, 0, $1, 0, 0, 0);}
    | '!' expr {$$ = astreeCreate(AST_NEG, 0, $2, 0 , 0, 0);}
    | expr OPERATOR_LE expr {$$ = astreeCreate(AST_LE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_GE expr {$$ = astreeCreate(AST_GE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_EQ expr {$$ = astreeCreate(AST_EQ, 0, $1, $3, 0, 0);}
    | expr OPERATOR_NE expr {$$ = astreeCreate(AST_NE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_AND expr {$$ = astreeCreate(AST_AND, 0, $1, $3, 0, 0);}
    | expr OPERATOR_OR expr {$$ = astreeCreate(AST_OR, 0, $1, $3, 0, 0);}
    | expr '*' expr {$$ = astreeCreate(AST_MULT, 0, $1, $3, 0, 0);}
    | expr '+' expr {$$ = astreeCreate(AST_ADD, 0, $1, $3, 0, 0);}
    | expr '-' expr {$$ = astreeCreate(AST_SUB, 0, $1, $3, 0, 0);}
    | expr '/' expr {$$ = astreeCreate(AST_DIV, 0, $1, $3, 0, 0);}
    | expr '<' expr {$$ = astreeCreate(AST_LESS, 0, $1, $3, 0, 0);}
    | expr '>' expr {$$ = astreeCreate(AST_GREATER, 0, $1, $3, 0, 0);}
    ;

%%



void yyerror( char *what )
{
  fprintf(stderr, "Syntax Error at line: %d at token: %c \n",lineNumber,yytext[0]);
  exit(3);
}
