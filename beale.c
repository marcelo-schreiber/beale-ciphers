#include <stdio.h>
#include <stdlib.h>

#include "encode.h"
#include "decode.h"
#include "utils.h"

void clearLinkedList(LinkedList *list)
{
  Node *current = list->head;
  Node *next = NULL;

  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  free(list->head);
  free(list->tail);
  free(list);
};

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

  encodeGenerateLetters(letters, fp);
  encodeGenerateFileLetters(letters, "keyvalues.txt");
  encodeGenerateFileLettersStringEncoded(letters, "encoded.txt", "Hello World");

  printLetter(letters);

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    clearLinkedList(letters[i].codes);
  }

  free(letters);

  fclose(fp);

  return 0;
}