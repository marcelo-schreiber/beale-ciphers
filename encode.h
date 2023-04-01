#include <stdio.h>
#include <stdlib.h>

struct Letter
{
  unsigned int *codes;
  unsigned int size;
  unsigned int mem_size;
};

#define NUM_OF_CHARS 26 + 10 // 26 letters and 10 numbers
#define MAX_WORD_SIZE 255    // 255 characters

void printLetter(struct Letter *letter);
void initializeLetter(struct Letter *letter);
void initializeMultipleLetters(struct Letter *letters, int size);
void encodeGenerateLetters(struct Letter *letters, FILE *fp);