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
  FILE *book_cypher = fopen("words.txt", "r");

  if (book_cypher == NULL)
  {
    printf("Error opening file");
    return 1;
  }

  encodeGenerateLetters(letters, book_cypher);
  encodeGenerateFileLetters(letters, "keyvalues.txt");
  encodeGenerateFileLettersStringEncoded(letters, "encoded.txt", "Hello World");

  printLetter(letters);

  encodeFreePointersFromLetters(letters);

  free(letters);

  fclose(book_cypher);

  return 0;
}