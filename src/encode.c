#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "encode.h"
#include "utils.h"

#define WHITESPACE_CHAR_ENCODED -1
#define NEWLINE_CHAR_ENCODED -2

void encodeFreePointersFromLetters(struct Letter *letter)
{
  for (int i = 0; i < NUM_OF_CHARS; i++)
    clearLinkedList(letter[i].codes);
}

void printLetter(struct Letter *letter)
{
  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    if (letter[i].codes->size == 0)
      continue;

    printf("%d", letter[i].codes->size);

    printf("\n%c: ", arrIdxToChar(i));

    printLinkedList(letter[i].codes);
  };
}

void initializeLetter(struct Letter *letter)
{
  letter->codes = malloc(sizeof(LinkedList));
  initializeLinkedList(letter->codes);
  letter->size = 0;
}

void initializeMultipleLetters(struct Letter *letters, int size)
{
  // memset(letters, 0, sizeof(struct Letter) * size);
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
    exit(EXIT_FAILURE);
  }

  while (fscanf(fp, " %255s", word) != EOF)
  {
    int first_char_idx = charToArrIdx(word[0]);

    if (first_char_idx == -1) // if first character is not valid
      continue;

    // add to linked list at codes[first_char_idx]
    addLinkedList(letters[first_char_idx].codes, word_idx);
    word_idx++;
  }

  free(word);
}

void encodeGenerateFileLetters(struct Letter *letter, char *filename)
{
  FILE *fp = fopen(filename, "w");

  if (fp == NULL)
  {
    printf("Error opening file");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    if (letter[i].codes->size == 0)
      continue;

    printLinkedListInFile(letter[i].codes, fp, arrIdxToChar(i));
  };

  fclose(fp);
}

void encodeGenerateFileLettersStringEncoded(struct Letter *letter, char *encoded_message, char *filename_with_message_to_be_encoded)
{
  FILE *fp = fopen(encoded_message, "w");
  FILE *fp_message = fopen(filename_with_message_to_be_encoded, "r");

  if (fp == NULL || fp_message == NULL)
  {
    printf("Error opening file");
    exit(EXIT_FAILURE);
  }

  char ch;

  while ((ch = fgetc(fp_message)) != EOF)
  {
    if (ch == ' ')
    {
      fprintf(fp, "%d ", WHITESPACE_CHAR_ENCODED);
      continue;
    }

    if (ch == '\n')
    {
      fprintf(fp, "%d ", NEWLINE_CHAR_ENCODED);
      continue;
    }
    const int first_char_idx = charToArrIdx((ch));

    if (first_char_idx == -1) // if first character is not valid
      continue;

    Node *node = letter[first_char_idx].codes->head;
    unsigned int size = letter[first_char_idx].codes->size;

    if (size == 0)
      continue;

    for (unsigned int j = 0; j < rand() % size; j++)
      node = node->next;

    fprintf(fp, "%d ", node->data);
  };

  fclose(fp);
  fclose(fp_message);
}

void encodeByBook(char *book_filename, char *message_filename, char *encoded_message_filename, char *keys_filename)
{
  FILE *book_cypher = fopen(book_filename, "r");

  if (book_cypher == NULL)
  {
    printf("Error opening file");
    exit(EXIT_FAILURE);
  }

  struct Letter *letters = malloc(sizeof(struct Letter) * (NUM_OF_CHARS));

  if (letters == NULL)
  {
    printf("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  initializeMultipleLetters(letters, NUM_OF_CHARS);

  encodeGenerateLetters(letters, book_cypher);
  encodeGenerateFileLetters(letters, keys_filename);
  encodeGenerateFileLettersStringEncoded(letters, encoded_message_filename, message_filename);

  encodeFreePointersFromLetters(letters);

  free(letters);
  fclose(book_cypher);
}