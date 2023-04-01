#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "decode.h"
#include "encode.h"

// read the file of numbers and generate the letters
void decodeGenerateNumbers(struct Number *numbers_cypher, FILE *fp)
{
  int word_idx = 0;
  char *word = malloc(sizeof(char) * MAX_WORD_SIZE);

  if (word == NULL)
  {
    printf("Error allocating memory");
    exit(1);
  }

  while (fscanf(fp, " %255s", word) != EOF)
  {
    char first_char = (tolower(word[0]));

    // if the first character is not a letter or a number
    if (first_char < 'a' || (first_char > 'z' && first_char < '0') || first_char > '9')
      continue;

    // store in the word_idx a string of all first characters found
    // in the file
    int current_size = strlen(numbers_cypher[word_idx].codes);
    numbers_cypher[word_idx].codes = realloc(numbers_cypher[word_idx].codes, (sizeof(char) * current_size) + 1);
    numbers_cypher[word_idx].codes[current_size + 1] = first_char;

    word_idx++;
  }

  free(word);
}
