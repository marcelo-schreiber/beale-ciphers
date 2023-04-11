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

void encodeGenerateFileLettersStringEncoded(struct Letter *letter, char *encoded_message, char *filename_with_message_to_be_encoded)
{
  FILE *fp = fopen(encoded_message, "w");
  FILE *fp_message = fopen(filename_with_message_to_be_encoded, "r");

  if (fp == NULL || fp_message == NULL)
  {
    printf("Error opening file");
    exit(1);
  }

  char ch;

  while ((ch = fgetc(fp_message)) != EOF)
  {
    if (ch == ' ')
    {
      fprintf(fp, "%d ", -1);
      continue;
    }

    const int first_char_idx = charToArrIdx(tolower(ch));

    if (first_char_idx == -1) // if first character is not a letter or number
      continue;

    Node *node = letter[first_char_idx].codes->head;
    unsigned int size = letter[first_char_idx].codes->size;

    if (size == 0)
      continue;

    for (int j = 0; j < rand() % size; j++)
      node = node->next;

    fprintf(fp, "%d ", node->data);
  };

  fclose(fp);
}

// this segfaults at this file somehow!

// void encodeBySomeThing(char *book_filename, char *message_filename, char *encoded_message_filename, char *keys_filename)
// {
//   FILE *book_cypher = fopen("LivroCifra.txt", "r");
//   // encode("LivroCifra.txt", "MensagemOriginal.txt", "MensagemCodificada.txt", "keyvalues.txt");
//   if (book_cypher == NULL)
//   {
//     printf("Error opening file");
//     exit(1);
//   }

//   struct Letter *letters = malloc(sizeof(struct Letter) * NUM_OF_CHARS);

//   if (letters == NULL)
//   {
//     printf("Error allocating memory");
//     exit(1);
//   }
//   initializeMultipleLetters(letters, NUM_OF_CHARS);

//   encodeGenerateLetters(letters, book_cypher);
//   encodeGenerateFileLetters(letters, "keyvalues.txt");
//   encodeGenerateFileLettersStringEncoded(letters, "MensagemCodificada.txt", "MensagemOriginal.txt");

//   encodeFreePointersFromLetters(letters);
//   free(letters);
//   fclose(book_cypher);
// };