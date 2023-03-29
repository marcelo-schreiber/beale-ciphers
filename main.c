#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Letter
{
  int *codes;
} Letter;

#define MAX_NUM_OF_CODES_PER_CHAR 100 // 100 codes per letter at max
#define NUM_OF_CHARS 26 + 9           // 26 letters and 9 numbers
#define MAX_WORD_SIZE 1024            // 1024 characters

char ArrIdxToChar(int code)
{
  if (code < 26)
    return code + 'a';
  else
    return code + '0' - 26;
}

int CharToArrIdx(char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a';
  if (c >= '0' && c <= '9')
    return c - '0' + 26;
  else
    return -1;
}

void PrintLetter(Letter *letter)
{
  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    int j = 0;
    printf("\n%c:", ArrIdxToChar(i));

    while (letter[i].codes[j] != 0)
    {
      printf(" %d ", letter[i].codes[j]);
      j++;
    }
  };
}

int main(void)
{
  Letter *letters = malloc(sizeof(Letter) * (NUM_OF_CHARS));

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    letters[i].codes = malloc(sizeof(int) * MAX_NUM_OF_CODES_PER_CHAR);
    memset(letters[i].codes, 0, sizeof(int) * MAX_NUM_OF_CODES_PER_CHAR);
  }
  // read file and store first character of each letter
  FILE *fp = fopen("words.txt", "r");

  if (fp == NULL)
  {
    printf("Error opening file");
    return 1;
  }

  char *word = malloc(sizeof(char) * MAX_WORD_SIZE);
  int word_idx = 1;

  while (fscanf(fp, " %1023s", word) != EOF)
  {
    int i = 0;
    char firstCharIdx = CharToArrIdx(tolower(word[0]));

    if (firstCharIdx == -1) // if first character is not a letter or number
      continue;

    while (letters[firstCharIdx].codes[i] != 0) // find the first empty slot
      i++;

    letters[firstCharIdx].codes[i] = word_idx; // store the word index

    word_idx++;
  }

  PrintLetter(letters);

  free(word);
  free(letters);
  fclose(fp);

  return 0;
}