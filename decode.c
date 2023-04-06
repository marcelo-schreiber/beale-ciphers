#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "decode.h"
#include "utils.h"

// read the file of numbers and generate the letters
char *decodeGenerateNumbers(FILE *fp)
{
  char *numbers_cypher = malloc(sizeof(char) * 2);
  numbers_cypher[0] = ' ';
  numbers_cypher[1] = '\0';

  if (numbers_cypher == NULL)
  {
    printf("Error allocating memory");
    exit(1);
  }

  int word_idx = 0;
  char *word = malloc(sizeof(char) * 256);

  if (word == NULL)
  {
    printf("Error allocating memory");
    exit(1);
  }

  while (fscanf(fp, " %255s", word) != EOF)
  {
    char first_char = (tolower(word[0]));

    if (strlen(numbers_cypher) <= word_idx)
    {
      numbers_cypher = realloc(numbers_cypher, sizeof(char) * ((word_idx << 1) + 1)); // double the size
      if (numbers_cypher == NULL)
      {
        printf("Error allocating memory");
        exit(1);
      }
    }

    numbers_cypher[word_idx] = first_char;
    numbers_cypher[word_idx + 1] = '\0'; // add null terminator

    word_idx++;
  }

  // realloc to correct size
  numbers_cypher = realloc(numbers_cypher, sizeof(char) * (word_idx + 1));
  numbers_cypher[word_idx] = '\0';

  free(word);

  return numbers_cypher;
}

void decodeGenerateFileUsingCodesKeys(char *numbers_cypher, const char *filename, FILE *encoded_message_file)
{
  // -1 is space

  FILE *fp = fopen(filename, "w");

  if (fp == NULL)
  {
    printf("Error opening file");
    exit(1);
  }

  int number;

  while (fscanf(encoded_message_file, "%d", &number) != EOF)
  {
    if (number == -1)
      fprintf(fp, " ");
    else
      fprintf(fp, "%c", numbers_cypher[number]);
  }

  fclose(fp);
}

void decodeGenerateFileUsingCypherBook(FILE *cypher_book, const char *filename, FILE *encoded_message_file)
{

  char *numbers_cypher = decodeGenerateNumbers(cypher_book);

  decodeGenerateFileUsingCodesKeys(numbers_cypher, filename, encoded_message_file);

  free(numbers_cypher);
}