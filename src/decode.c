#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "decode.h"
#include "utils.h"

#define REALLOC_SIZE_OFFSET 1024

// read the file of numbers and generate the letters
char *decodeGenerateNumbers(FILE *fp)
{
  unsigned int array_size = 2;
  char *numbers_cypher = malloc(sizeof(char) * array_size);
  unsigned int word_idx = 0;
  char *word = malloc(sizeof(char) * 256);
  numbers_cypher[0] = ' ';
  numbers_cypher[1] = '\0';

  if (numbers_cypher == NULL)
  {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  if (word == NULL)
  {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  while (fscanf(fp, " %s", word) != EOF)
  {
    char first_char = word[0];

    if (charToArrIdx(first_char) == -1)
      continue;

    if (array_size <= word_idx)
    {
      array_size <<= 1;
      numbers_cypher = realloc(numbers_cypher, sizeof(char) * array_size); // double the size
      if (numbers_cypher == NULL)
      {
        printf("Error allocating memory");
        exit(EXIT_FAILURE);
      }
    }

    numbers_cypher[word_idx] = first_char;

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
    exit(EXIT_FAILURE);
  }

  int number;
  while (fscanf(encoded_message_file, "%d", &number) != EOF)
  {

    if (number == -1)
      fprintf(fp, " ");
    else if (number == -2)
      fprintf(fp, "\n");
    else
      fprintf(fp, "%c", numbers_cypher[number]);
  }

  fclose(fp);
}

char *decodeGenerateNumbersUsingCodeskeys(const char *filename)
{
  FILE *fp = fopen(filename, "r");

  if (fp == NULL)
  {
    printf("Error opening file");
    exit(EXIT_FAILURE);
  }

  // a: 15 31 35 48 59 63 65 72 85 89
  // c: 10 32 41 42 68 70 79
  // d: 7 18 20 33 36 46 56 58 61 64 67 80 83 86
  // e: 0 37 40 51 53 62 77 96
  // f: 6 17 24 25 28 69
  // i: 3 30 47 88
  // o: 2 13 22 39 93 98
  // 1: 1 38
  // ...

  // transform into
  // 0: e
  // 1: 1
  // 2: o
  // ...

  char *numbers_cypher = malloc(sizeof(char));
  numbers_cypher[0] = ' ';

  if (numbers_cypher == NULL)
  {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  char letter;

  char line[10000];
  int biggest_num = -2;
  char *token;

  while (fgets(line, 10000, fp) != NULL)
  {
    letter = line[0];
    token = strtok(line, " ");

    while (token != NULL)
    {
      if (strlen(token) == 2 && token[1] == ':')
      {
        token = strtok(NULL, " ");
        continue;
      }
      if (strlen(token) == 1 && token[0] == '\n')
      {
        token = strtok(NULL, " ");
        continue;
      }

      int number = atoi(token);

      if (number >= biggest_num)
      {
        biggest_num = number;
        numbers_cypher = realloc(numbers_cypher, sizeof(char) * (biggest_num + 2));

        if (numbers_cypher == NULL)
        {
          printf("Error allocating memory");
          exit(EXIT_FAILURE);
        }
      }

      numbers_cypher[number] = letter;

      token = strtok(NULL, " ");
    }
  }

  if (biggest_num < 1) // if there is no numbers
  {
    printf("Error: no numbers in the file");
    exit(EXIT_FAILURE);
  }

  numbers_cypher = realloc(numbers_cypher, sizeof(char) * (biggest_num + 2));

  numbers_cypher[biggest_num + 1] = '\0';

  free(token);
  fclose(fp);

  return numbers_cypher;
}

void decodeGenerateFileUsingCypherBook(FILE *cypher_book, const char *filename, FILE *encoded_message_file)
{
  char *numbers_cypher = decodeGenerateNumbers(cypher_book);

  decodeGenerateFileUsingCodesKeys(numbers_cypher, filename, encoded_message_file);

  free(numbers_cypher);
}

void decodeByKeys(char *encoded_message_filename, char *keys_filename, char *decoded_message_filename)
{
  FILE *encoded_message_file = fopen(encoded_message_filename, "r");

  if (encoded_message_file == NULL)
  {
    printf("Error opening file");
    exit(EXIT_FAILURE);
  }

  char *numbers = decodeGenerateNumbersUsingCodeskeys(keys_filename);

  decodeGenerateFileUsingCodesKeys(numbers, decoded_message_filename, encoded_message_file);

  fclose(encoded_message_file);
  free(numbers);
}

void decodeByBook(char *encoded_message_filename, char *book_filename, char *decoded_message_filename)
{
  FILE *encoded_message_file = fopen(encoded_message_filename, "r");

  if (encoded_message_file == NULL)
  {
    printf("Error opening file");
    exit(EXIT_FAILURE);
  }

  FILE *book_file = fopen(book_filename, "r");

  if (book_file == NULL)
  {
    printf("Error opening file");
    exit(EXIT_FAILURE);
  }

  decodeGenerateFileUsingCypherBook(book_file, decoded_message_filename, encoded_message_file);

  fclose(encoded_message_file);
  fclose(book_file);
}