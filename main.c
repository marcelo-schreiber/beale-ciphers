#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Letter
{
  int *codes;
} Letter;

#define MAX_NUM_OF_CODES_PER_CHAR 100
#define NUM_OF_CHARS 26 + 9

char arr_idx_to_char(int code)
{
  if (code < 26)
    return code + 'a';
  else
    return code + '0' - 26;
}

int char_to_arr_idx(char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a';
  if (c >= '0' && c <= '9')
    return c - '0' + 26;
  else
    return -1;
}

void print_letter(Letter *letter)
{
  for (int i = 0; i < NUM_OF_CHARS; i++)
  {
    int j = 0;
    printf("\n%c:", arr_idx_to_char(i));

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

  char *word = malloc(100 * sizeof(char));
  size_t len = 0;
  size_t read;
  int word_idx = 1;

  while (fscanf(fp, " %1023s", word) != EOF)
  {
    int i = 0;
    char firstCharIdx = char_to_arr_idx(tolower(word[0]));

    if (firstCharIdx == -1) // if first character is not a letter or number
      continue;

    while (letters[firstCharIdx].codes[i] != 0) // find the first empty slot
      i++;

    letters[firstCharIdx].codes[i] = word_idx; // store the word index

    word_idx++;
  }

  print_letter(letters);

  free(word);
  free(letters);
  fclose(fp);

  return 0;
}