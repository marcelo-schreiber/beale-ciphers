#include <stdlib.h>
#include "../include/utils.h"

inline char arrIdxToChar(int code)
{
  if (code < 0 || code > NUM_OF_CHARS - 1)
    return -1;
  return code + FIRST_CHAR;
}

inline int charToArrIdx(char c)
{
  if (c < FIRST_CHAR || c > LAST_CHAR)
    return -1;
  return c - FIRST_CHAR;
}