#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "encode.h"
#include "decode.h"
#include "utils.h"

/*
Codificar uma mensagem qualquer contida em um arquivo ASCII usando um livro cifra. O programa deve ter uma opção de salvar em um arquivo texto as chaves geradas no formato descrito anteriormente. A linha de execução do programa dever ser a seguinte:

./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves
Decodificar uma mensagem, usando um arquivo de códigos
./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada
Decodificar uma mensagem usando o livro cifra
./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada
*/
void encode(char *book_filename, char *message_filename, char *encoded_message_filename, char *keys_filename)
{
  FILE *book_cypher = fopen(book_filename, "r");

  if (book_cypher == NULL)
  {
    printf("Error opening file");
    exit(1);
  }

  struct Letter *letters = malloc(sizeof(struct Letter) * (NUM_OF_CHARS));

  if (letters == NULL)
  {
    printf("Error allocating memory");
    exit(1);
  }

  initializeMultipleLetters(letters, NUM_OF_CHARS);

  encodeGenerateLetters(letters, book_cypher);
  encodeGenerateFileLetters(letters, keys_filename);
  encodeGenerateFileLettersStringEncoded(letters, encoded_message_filename, message_filename);

  encodeFreePointersFromLetters(letters);

  free(letters);
  fclose(book_cypher);
}

int main(int argc, char *argv[])
{
  encode("LivroCifra.txt", "MensagemOriginal.txt", "MensagemCodificada.txt", "ArquivoDeChaves.txt");
  decodeByBook("MensagemCodificada.txt", "LivroCifra.txt", "MensagemDecodificada.txt");
  decodeByKeys("MensagemCodificada.txt", "ArquivoDeChaves.txt", "MensagemDecodificada2.txt");
  // FILE *book_cypher = fopen("LivroCifra.txt", "r");

  // if (book_cypher == NULL)
  // {
  //   printf("Error opening file");
  //   return 1;
  // }

  // struct Letter *letters = malloc(sizeof(struct Letter) * (NUM_OF_CHARS));

  // if (letters == NULL)
  // {
  //   printf("Error allocating memory");
  //   return 1;
  // }

  // initializeMultipleLetters(letters, NUM_OF_CHARS);

  // encodeGenerateLetters(letters, book_cypher);
  // printLetter(letters);
  // encodeGenerateFileLetters(letters, "keyvalues.txt");
  // encodeGenerateFileLettersStringEncoded(letters, "MensagemCodificada.txt", "MensagemOriginal.txt");

  // encodeFreePointersFromLetters(letters);

  // free(letters);
  // fclose(book_cypher);
}
