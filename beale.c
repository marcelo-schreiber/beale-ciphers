#include <stdio.h>
#include <stdlib.h>

#include "encode.h"
#include "decode.h"
#include "utils.h"

int main(void)
{
  // FILE *book_cypher = fopen("words.txt", "r");

  // if (book_cypher == NULL)
  // {
  //   printf("Error opening file");
  //   return 1;
  // }

  // struct Letter *letters = malloc(sizeof(struct Letter) * (NUM_OF_CHARS));

  // if (letters == NULL)
  // {
  //   printf("Error allocating memory");
  //   return 1;
  // }

  // initializeMultipleLetters(letters, NUM_OF_CHARS);

  // encodeGenerateLetters(letters, book_cypher);
  // // encodeGenerateFileLetters(letters, "keyvalues.txt");
  // // encodeGenerateFileLettersStringEncoded(letters, "encoded.txt", "Hello World");

  // // printLetter(letters);

  // // encodeFreePointersFromLetters(letters);

  // free(letters);

  char *numbers = decodeGenerateNumbersUsingCodeskeys("keyvalues.txt");
  // char *numbers2 = decodeGenerateNumbers(book_cypher);
  printf("%s\n", numbers);
  // printf("%s\n", numbers2);
  free(numbers);
  return 0;
}