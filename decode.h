#include <stdio.h>
#include <stdlib.h>

char *decodeGenerateNumbers(FILE *fp);
void decodeGenerateFileUsingCodesKeys(char *numbers_cypher, const char *filename, FILE *encoded_message_file);
void decodeGenerateFileUsingCypherBook(FILE *cypher_book, const char *filename, FILE *encoded_message_file);
char *decodeGenerateNumbersUsingCodeskeys(const char *filename);
void decodeByKeys(char *encoded_message_filename, char *keys_filename, char *decoded_message_filename);
void decodeByBook(char *encoded_message_filename, char *book_filename, char *decoded_message_filename);