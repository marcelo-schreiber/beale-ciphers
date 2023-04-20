#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "encode.h"
#include "decode.h"
#include "utils.h"

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
  int has_encode = 0;
  int has_decode = 0;
  int has_book = 0;
  int has_message = 0;
  int has_input = 0;
  int has_key = 0;
  int has_output = 0;

  char *book_path = NULL;
  char *message_path = NULL;
  char *input_path = NULL;
  char *key_path = NULL;
  char *output_path = NULL;

  int opt;
  while ((opt = getopt(argc, argv, "edb:m:i:o:c:")) != -1)
  {
    switch (opt)
    {
    case 'e':
      has_encode = 1;
      break;
    case 'd':
      has_decode = 1;
      break;
    case 'b':
      has_book = 1;
      book_path = optarg;
      break;
    case 'm':
      has_message = 1;
      message_path = optarg;
      break;
    case 'i':
      has_input = 1;
      input_path = optarg;
      break;
    case 'c':
      has_key = 1;
      key_path = optarg;
      break;
    case 'o':
      has_output = 1;
      output_path = optarg;
      break;
    default:
      //  ./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves
      // ./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada
      // ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada
      fprintf(stderr, "Uso: %s [-e] [-b] [-m] [-o] [-c] ou %s [-d] [-i] [-c] [-o] ou %s [-d] [-i] [-b] [-o] (com terminação de arquivos, Ex.: arq.txt ou arq.ascii)", argv[0], argv[0], argv[0]);
      exit(EXIT_FAILURE);
    }
  };

  if (has_encode)
  {
    if (!(has_book && has_message && has_output && has_key))
    {
      fprintf(stderr, "Uso: %s -e -b book_path -m message_path -o output_path -c key_path", argv[0]);
      exit(EXIT_FAILURE);
    }

    // TODO: verificar se os arquivos existem
    encodeByBook(book_path, message_path, output_path, key_path);
  }
  else if (has_decode)
  {
    if (has_input && has_key && has_output)
      decodeByKeys(input_path, key_path, output_path);
    else if (has_input && has_book && has_output)
      decodeByBook(input_path, book_path, output_path);
    else
    {
      fprintf(stderr, "Uso: %s -d -i input_path -c key_path -o output_path ou %s -d -i input_path -b book_path -o output_path", argv[0], argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    fprintf(stderr, "Uso: %s [-e] [-b] [-m] [-o] [-c] ou %s [-d] [-i] [-c] [-o] ou %s [-d] [-i] [-b] [-o] (com terminação de arquivos, Ex.: arq.txt ou arq.ascii)", argv[0], argv[0], argv[0]);
    exit(EXIT_FAILURE);
  }
}