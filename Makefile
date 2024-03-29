#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#


etapa2: y.tab.c lex.yy.c main.c
	gcc lex.yy.c -o etapa3

y.tab.c: parser.y
	yacc -d parser.y -v

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa3 lex.yy.c y.tab.c
