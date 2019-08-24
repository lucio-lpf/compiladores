#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"


void initMe(){

  int i;
  for (i=0;i<HASH_SIZE;i++){
    Table[i] = 0;
  }
}

int hashAddress(char *text){

  int i;
  int address = 1;
  for (i=0;i<strlen(text);i++){
    address = (address * text[i]) % HASH_SIZE + 1;
  }
  return address - 1;
}

HASH_NODE * hashFind(char * text){

  int address = hashAddress(text);
  HASH_NODE *findNode = Table[address];
  for (findNode = Table[address]; findNode != 0; findNode = findNode->next){
	if(strcmp(text,findNode->text) == 0) return findNode;
	}
  return 0;
}

HASH_NODE *hashInsert(int type, char *text){

  HASH_NODE *newnode;
  int address = hashAddress(text);
  newnode = calloc(1, sizeof(HASH_NODE));
  newnode->type = type;
  newnode->text = calloc(strlen(text)+1,sizeof(char));
  strcpy(newnode->text, text);
  newnode->next = Table[address];
  Table[address] = newnode;
  return newnode;
}
void hashPrint(){
  int i;
  HASH_NODE *node;
  for (i=0;i<HASH_SIZE;i++){
    for (node = Table[i]; node; node = node->next){
      printf("Table[%d]has %s\n",i,node->text);
    }
  }
}
