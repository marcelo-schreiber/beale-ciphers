#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "encode.h"

char arrIdxToChar(int code)
{
  if (code < 26)
    return code + 'a';
  if (code >= 26 && code < 36)
    return code + '0' - 26;
  else
    return -1;
}

int charToArrIdx(char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a';
  if (c >= '0' && c <= '9')
    return c - '0' + 26;
  else
    return -1;
}

void printLetter(struct Letter *letter)
{
  int j;

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    j = 0;
    if (letter[i].size == 0)
      continue;

    printf("\n%c:", arrIdxToChar(i));

    while (j < letter[i].size)
    {
      printf(" %d ", letter[i].codes[j]);
      j++;
    }
  };
}

void initializeLetter(struct Letter *letter)
{
  letter->codes = malloc(sizeof(int));
  letter->codes[0] = 0;
  letter->size = 0;
  letter->mem_size = 1;
}

void initializeMultipleLetters(struct Letter *letters, int size)
{
  memset(letters, 0, sizeof(*letters));
  for (int i = 0; i < size; i++)
    initializeLetter(&letters[i]);
}

void generateLetters(struct Letter *letters, FILE *fp)
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
    int first_char_idx = charToArrIdx(tolower(word[0]));

    if (first_char_idx == -1) // if first character is not a letter or number
      continue;

    if (++(letters[first_char_idx].size) > letters[first_char_idx].mem_size) // if size is bigger than memory size, double memory size, this prevents too much reallocation
    {
      letters[first_char_idx].mem_size <<= 1;
      letters[first_char_idx].codes = realloc(letters[first_char_idx].codes, sizeof(int) * letters[first_char_idx].mem_size);

      if (letters[first_char_idx].codes == NULL)
      {
        printf("Error allocating memory");
        exit(1);
      }
    }

    letters[first_char_idx].codes[letters[first_char_idx].size - 1] = word_idx; // store word index in array of codes in position of size

    word_idx++;
  }
  free(word);

  // realloc to the exact size
  for (int i = 0; i < NUM_OF_CHARS; i++)
  {

    letters[i].mem_size = letters[i].size;
    if (letters[i].size == 0)
    {
      free(letters[i].codes);
      letters[i].codes = NULL;
      continue;
    }
    letters[i].codes = realloc(letters[i].codes, sizeof(int) * letters[i].size);
  }
}
