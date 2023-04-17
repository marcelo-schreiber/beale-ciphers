#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
struct Letter
{
  LinkedList *codes;
  unsigned int size;
};

void encodeByBook(char *book_filename, char *message_filename, char *encoded_message_filename, char *keys_filename);