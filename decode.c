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

char *decodeGenerateNumbersUsingCodeskeys(const char *filename)
{
  FILE *fp = fopen(filename, "r");

  if (fp == NULL)
  {
    printf("Error opening file");
    exit(1);
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
    exit(1);
  }

  char letter;

  char line[255];
  int biggest_num = -1;
  char *token;

  while (fgets(line, 255, fp) != NULL)
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

      if (number > biggest_num)
      {
        biggest_num = number;
        numbers_cypher = realloc(numbers_cypher, sizeof(char) * (biggest_num + 2));

        if (numbers_cypher == NULL)
        {
          printf("Error allocating memory");
          exit(1);
        }
      }

      numbers_cypher[number] = letter;

      token = strtok(NULL, " ");
    }
  }

  numbers_cypher[biggest_num + 1] = '\0';

  fclose(fp);

  return numbers_cypher;
}

void decodeGenerateFileUsingCypherBook(FILE *cypher_book, const char *filename, FILE *encoded_message_file)
{

  char *numbers_cypher = decodeGenerateNumbers(cypher_book);

  decodeGenerateFileUsingCodesKeys(numbers_cypher, filename, encoded_message_file);

  free(numbers_cypher);
}