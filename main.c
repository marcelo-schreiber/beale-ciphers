#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Letter
{
  int *codes;
  unsigned int size;
  unsigned int mem_size;
} Letter;

#define NUM_OF_CHARS 26 + 10 // 26 letters and 10 numbers
#define MAX_WORD_SIZE 255    // 1024 characters

char ArrIdxToChar(int code)
{
  if (code < 26)
    return code + 'a';
  if (code >= 26 && code < 36)
    return code + '0' - 26;
  else
    return -1;
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
  int j;

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    j = 0;
    int size = letter[i].size;
    if (size == 0)
      continue;

    printf("\n%c:", ArrIdxToChar(i));

    while (j < size)
    {
      printf(" %d ", letter[i].codes[j]);
      j++;
    }
  };
}

int main(void)
{
  Letter *letters = malloc(sizeof(Letter) * (NUM_OF_CHARS));
  memset(letters, 0, sizeof(*letters));

  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    letters[i].codes = malloc(sizeof(int));
    letters[i].codes[0] = 0;
    letters[i].size = 0;
    letters[i].mem_size = 1;
  }
  // read file and store first character of each letter
  FILE *fp = fopen("words.txt", "r");

  if (fp == NULL)
  {
    printf("Error opening file");
    return 1;
  }

  char *word = malloc(sizeof(char) * MAX_WORD_SIZE);

  if (word == NULL)
  {
    printf("Error allocating memory");
    return 1;
  }

  int word_idx = 0;

  while (fscanf(fp, " %255s", word) != EOF)
  {
    char firstCharIdx = CharToArrIdx(tolower(word[0]));

    if (firstCharIdx == -1) // if first character is not a letter or number
      continue;

    if (++(letters[firstCharIdx].size) > letters[firstCharIdx].mem_size) // if size is bigger than memory size, double memory size, this prevents too much reallocation
    {
      letters[firstCharIdx].mem_size = letters[firstCharIdx].mem_size * 2;
      letters[firstCharIdx].codes = realloc(letters[firstCharIdx].codes, sizeof(int) * letters[firstCharIdx].mem_size);

      if (letters[firstCharIdx].codes == NULL)
      {
        printf("Error allocating memory");
        return 1;
      }
    }
    letters[firstCharIdx].codes[letters[firstCharIdx].size - 1] = word_idx; // store word index in array of codes in position of size

    word_idx++;
  }

  PrintLetter(letters);

  free(word);
  for (int i = 0; i < NUM_OF_CHARS; i++)
    free(letters[i].codes);
  free(letters);

  fclose(fp);

  return 0;
}