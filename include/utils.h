#include <stdlib.h>

#define NUM_OF_CHARS 93 // from 33 to 126 (33 to 126 - 33 = 93) (from ! to ~)
#define FIRST_CHAR '!'
#define LAST_CHAR '~'
#define MAX_WORD_SIZE 255 // 255 characters

char arrIdxToChar(int code);
int charToArrIdx(char c);
