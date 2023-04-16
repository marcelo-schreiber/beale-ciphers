#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "../include/encode.h"
#include "../include/decode.h"
#include "../include/utils.h"

/* Codificar uma mensagem qualquer contida em um arquivo ASCII usando um livro cifra. O programa deve ter uma opção de salvar em um arquivo texto as chaves geradas no formato descrito anteriormente. A linha de execução do programa dever ser a seguinte:

./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves
Decodificar uma mensagem, usando um arquivo de códigos
./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada
Decodificar uma mensagem usando o livro cifra
./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada
 */

// TODO: trocar fgets por fscanf para gerar arquivo chave (encode.c)
int main(int argc, char *argv[])
{
  int opt;

  int encode = 0;
  int decode = 0;
  int book = 0;
  int message = 0;
  int input = 0;
  int key = 0;
  int output = 0;

  char *book_path = NULL;
  char *message_path = NULL;
  char *input_path = NULL;
  char *key_path = NULL;
  char *output_path = NULL;

  while ((opt = getopt(argc, argv, "edb:m:i:o:c:")) != -1)
  {
    switch (opt)
    {
    case 'e':
      encode = 1;
      break;
    case 'd':
      decode = 1;
      break;
    case 'b':
      book = 1;
      book_path = optarg;
      break;
    case 'm':
      message = 1;
      message_path = optarg;
      break;
    case 'i':
      input = 1;
      input_path = optarg;
      break;
    case 'c':
      key = 1;
      key_path = optarg;
      break;
    case 'o':
      output = 1;
      output_path = optarg;
      break;
    default:
      fprintf(stderr, "Uso: %s [-e|-d] [-b book_path] [-m message_path] [-i input_path] [-c key_path] [-o output_path]", argv[0]);
      exit(EXIT_FAILURE);
    }
  };

  if (encode)
  {
    if (!(book && message && output && key))
    {
      fprintf(stderr, "Uso: %s -e -b book_path -m message_path -o output_path -c key_path", argv[0]);
      exit(EXIT_FAILURE);
    }
    encodeByBook(book_path, message_path, output_path, key_path);
  }
  else if (decode)
  {
    if (input && key && output)
      decodeByKeys(input_path, key_path, output_path);
    else if (input && book && output)
      decodeByBook(input_path, book_path, output_path);
    else
    {
      fprintf(stderr, "Uso: %s -d -i input_path -c key_path -o output_path ou %s -d -i input_path -b book_path -o output_path", argv[0], argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    fprintf(stderr, "Uso: %s [-e] [-d] [-b book_path] [-m message_path] [-i input_path] [-c key_path] [-o output_path]", argv[0]);
    exit(EXIT_FAILURE);
  }
}