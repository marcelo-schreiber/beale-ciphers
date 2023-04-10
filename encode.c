#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "encode.h"
#include "utils.h"

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
    exit(1);
  }

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    if (letter[i].codes->size == 0)
      continue;

    printLinkedListInFile(letter[i].codes, fp, arrIdxToChar(i));
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
    if (message_to_be_encoded[i] == ' ')
    {
      fprintf(fp, "%d ", -1);
      continue;
    }

    const int first_char_idx = charToArrIdx(tolower(message_to_be_encoded[i]));

    if (first_char_idx == -1) // if first character is not a letter or number
      continue;

    Node *node = letter[first_char_idx].codes->head;
    unsigned int size = letter[first_char_idx].codes->size;

    for (int j = 0; j < rand()%size; j++)
      node = node->next;


    fprintf(fp, "%d ", node->data);
  };

  fclose(fp);
}