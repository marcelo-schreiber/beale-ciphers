#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "encode.h"
#include "utils.h"

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

void encodeGenerateLetters(struct Letter *letters, FILE *fp)
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
      letters[i].codes = NULL; // set to NULL so it can be freed later
      continue;
    }
    letters[i].codes = realloc(letters[i].codes, sizeof(int) * letters[i].size);
  }
}

void encodeGenerateFileLetters(struct Letter *letter, char *filename)
{
  int j;

  FILE *fp = fopen(filename, "w");

  if (fp == NULL)
  {
    printf("Error opening file");
    exit(1);
  }

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    j = 0;
    if (letter[i].size == 0)
      continue;

    fprintf(fp, "\n%c:", arrIdxToChar(i));

    while (j < letter[i].size)
    {
      fprintf(fp, " %d ", letter[i].codes[j]);
      j++;
    }
  };

  fclose(fp);
}

void encodeGenerateFileLettersStringEncoded(struct Letter *letter, char *filename, char *message_to_be_encoded)
{

  FILE *fp = fopen(filename, "w");

  if (fp == NULL)
  {
    printf("Error opening file");
    exit(1);
  }

  for (int i = 0; i < strlen(message_to_be_encoded); i++)
  {
    if (message_to_be_encoded[i] == -1)
      fprintf(fp, " ");

    if (letter[i].size == 0)
      continue;

    fprintf(fp, "%d ", arrIdxToChar(letter[i].codes[0]));
  };

  fclose(fp);
}