#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

void initializeLinkedList(LinkedList *list)
{
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
};
void addLinkedList(LinkedList *list, unsigned int data)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;

  if (list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else
  {
    list->tail->next = newNode;
    list->tail = newNode;
  }
  ++(list->size);
};

void removeLinkedList(LinkedList *list, unsigned int data)
{
  Node *current = list->head;
  Node *previous = NULL;

  while (current != NULL)
  {
    if (current->data == data)
    {
      if (previous == NULL)
        list->head = current->next;
      else
        previous->next = current->next;

      free(current);
      list->size--;
      return;
    }
    previous = current;
    current = current->next;
  }
};

void printLinkedList(LinkedList *list)
{
  Node *current = list->head;
  while (current != NULL)
  {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
};

void printLinkedListInFile(LinkedList *list, FILE *fp, char index)
{
  Node *current = list->head;
  fprintf(fp, "%c: ", index);
  while (current != NULL)
  {
    fprintf(fp, "%d ", current->data);
    current = current->next;
  }
  fprintf(fp, "\n");
};

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
