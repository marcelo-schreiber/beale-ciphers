#include <stdlib.h>
typedef struct Node
{
  unsigned int data;
  struct Node *next;
} Node;

typedef struct LinkedList
{
  Node *tail;
  Node *head;
  unsigned int size;
} LinkedList;

void initializeLinkedList(LinkedList *list);
void addLinkedList(LinkedList *list, unsigned int data);
void removeLinkedList(LinkedList *list, unsigned int data);
void printLinkedList(LinkedList *list);
void printLinkedListInFile(LinkedList *list, FILE *fp, char index);
void clearLinkedList(LinkedList *list);