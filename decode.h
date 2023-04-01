#include <stdio.h>
#include <stdlib.h>

struct Number
{
  char *codes;
  unsigned int size;
};

void decodeGenerateNumbers(struct Number *numbers_cypher, FILE *fp);