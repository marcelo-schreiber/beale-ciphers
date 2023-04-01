#include <stdio.h>
#include <stdlib.h>

#include "encode.h"

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

  printLetter(letters);

  for (int i = 0; i < NUM_OF_CHARS; i++)
    free(letters[i].codes);
  free(letters);

  fclose(fp);

  return 0;
}