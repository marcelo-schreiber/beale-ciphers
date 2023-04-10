#include <stdio.h>
#include <stdlib.h>

char *decodeGenerateNumbers(FILE *fp);
void decodeGenerateFileUsingCodesKeys(char *numbers_cypher, const char *filename, FILE *encoded_message_file);
void decodeGenerateFileUsingCypherBook(FILE *cypher_book, const char *filename, FILE *encoded_message_file);
char *decodeGenerateNumbersUsingCodeskeys(const char *filename);