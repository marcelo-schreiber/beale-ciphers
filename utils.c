#include <stdlib.h>
#include "utils.h"

char arrIdxToChar(int code)
{
  if (code < 26)
    return code + 'a';
  if (code >= 26 && code < 36)
    return code + '0' - 26;
  else
    return -1;
}

int charToArrIdx(char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a';
  if (c >= '0' && c <= '9')
    return c - '0' + 26;
  else
    return -1;
}