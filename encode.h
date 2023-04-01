#include <stdio.h>
#include <stdlib.h>

struct Letter
{
  unsigned int *codes;
  unsigned int size;
  unsigned int mem_size;
};

void printLetter(struct Letter *letter);
void initializeLetter(struct Letter *letter);
void initializeMultipleLetters(struct Letter *letters, int size);
void encodeGenerateLetters(struct Letter *letters, FILE *fp);