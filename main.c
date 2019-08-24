#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "astree.h"

int main(int argc, char **argv)
{

  initMe();
  running = 1;
  if(argc<3)
   {
  	fprintf(stderr, "please: ./a.out read_file_name exit_file_name.\n");
  	exit(1);
   }
  if(!(yyin = fopen(argv[1], "r")))
   {
  	fprintf(stderr, "Cannot Open: %s \n", argv[1]);
  	exit(2);
   }
  if(!(FileTree = fopen(argv[2],"w")))
   {
	fprintf(stderr, "Cannot Create: %s \n",argv[2]);
	exit(2);
   }


  initMe();
  yyparse();
  printf("sucesso\n");
  exit(0);
}
