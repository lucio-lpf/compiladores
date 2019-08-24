#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

typedef struct hash_struct{

  int type;
  char *text;
  struct hash_struct *next;

} HASH_NODE;

HASH_NODE* Table[HASH_SIZE];

void initMe();
int hashAddress(char *text);
HASH_NODE * hashFind(char *text);
HASH_NODE * hashInsert(int type, char *text);
void hashPrint();

#endif
