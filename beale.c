#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encode.h"
#include "decode.h"
#include "utils.h"

int main(int argc, char *argv[])
{
  // ./beale -e -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves
  // ./beale -d -i MensagemCodificada -c ArquivoDeChaves -o MensagemDecodificada
  // ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada

  if (argc != 8 && argc != 10)
  {
    printf("Invalid number of arguments");
    return 1;
  }

  if (strcmp(argv[1], "-e") == 0 && argc == 10) // if is encoding
  {
    const char *book_cypher = argv[3];
    const char *message_original = argv[5];
    const char *message_encoded = argv[7];
    const char *key_file = argv[9];

    FILE *book_cypher_file = fopen(book_cypher, "r");

    if (book_cypher_file == NULL)
    {
      printf("Error opening file");
      return 1;
    }

    struct Letter *letters = malloc(sizeof(struct Letter) * (NUM_OF_CHARS));

    if (letters == NULL)
    {
      printf("Error allocating memory");
      return 1;
    }

    initializeMultipleLetters(letters, NUM_OF_CHARS);

    encodeGenerateLetters(letters, book_cypher_file);
    encodeGenerateFileLetters(letters, key_file);
    encodeGenerateFileLettersStringEncoded(letters, message_encoded, message_original);

    encodeFreePointersFromLetters(letters);

    free(letters);

    fclose(book_cypher);

    return 0;
  }

  if (argc == 10 && strcmp(argv[1], "-d") == 0) // if is decoding
  {
    const char *message_encoded = argv[3];
    const char *key_file = argv[5];
    const char *message_decoded = argv[7];

    FILE *message_encoded_file = fopen(message_encoded, "r");

    return 0;
  }

  return 0;
}