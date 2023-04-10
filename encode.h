#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
struct Letter
{
  LinkedList *codes;
  unsigned int size;
};

void printLetter(struct Letter *letter);
void initializeLetter(struct Letter *letter);
void initializeMultipleLetters(struct Letter *letters, int size);
void encodeGenerateLetters(struct Letter *letters, FILE *fp);
void encodeGenerateFileLetters(struct Letter *letters, char *filename);
void encodeGenerateFileLettersStringEncoded(struct Letter *letter, char *filename, char *message_to_be_encoded);
void encodeFreePointersFromLetters(struct Letter *letter);