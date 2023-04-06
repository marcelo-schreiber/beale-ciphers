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
  FILE *encoded = fopen("numbers.txt", "r");

  if (fp == NULL || encoded == NULL)
  {
    printf("Error opening file");
    return 1;
  }

  encodeGenerateLetters(letters, fp);

  // reset pointer to initial of the file
  rewind(fp);

  char *numbers_cypher = decodeGenerateNumbers(fp);
  printf("cp: %s\n\n", numbers_cypher);
  encodeGenerateFileLettersStringEncoded(letters, "coded.txt", "Hej");
  rewind(fp);
  decodeGenerateFileUsingCypherBook(fp, "decoded2.txt", encoded);

  for (int i = 0; i < NUM_OF_CHARS; i++)
    free(letters[i].codes);
  free(letters);

  free((char *)numbers_cypher);

  fclose(fp);
  fclose(encoded);

  return 0;
}