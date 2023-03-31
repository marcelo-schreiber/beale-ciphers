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

  generateLetters(letters, fp);

  printLetter(letters);

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    if (letters[i].codes != NULL || letters[i].mem_size != 0) // if the letter is not empty or already was freed
      free(letters[i].codes);
  }
  free(letters);

  fclose(fp);

  return 0;
}