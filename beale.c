#include <stdio.h>
#include <stdlib.h>

#include "encode.h"
#include "decode.h"
#include "utils.h"

int main(void)
{
  struct Letter *letters = malloc(sizeof(struct Letter) * (NUM_OF_CHARS));
  initializeMultipleLetters(letters, NUM_OF_CHARS);
  // read file and store first character of each letter
  FILE *fp = fopen("words.txt", "r");

  if (fp == NULL)
  {
    printf("Error opening file");
    return 1;
  }

  encodeGenerateLetters(letters, fp);
  encodeGenerateFileLetters(letters, "keyvalues.txt");
  encodeGenerateFileLettersStringEncoded(letters, "encoded.txt", "Hello World");

  printLetter(letters);

  freePointersFromLetter(letters);

  free(letters);

  fclose(fp);

  return 0;
}