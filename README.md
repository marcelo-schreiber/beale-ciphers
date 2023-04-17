<!-- Arquivo LEIAME contendo nome e GRR do aluno, texto explicando resumidamente os módulos criados, as estruturas de dados e os algoritmos usados.  -->

<!-- Marcelo Augusto Rissette Schreiber - 20220063 -->

# Módulos criados

## `src/`

- `beale.c`: arquivo principal do programa, contém a função `main()`.
- `encode.c`: contém a função `encodeByBook()`, que codifica uma mensagem a partir de um livro usando a cifra de Beale.
- `decode.c`: contém a função `decodeByBook()`, que decodifica uma mensagem a partir de um livro usando a cifra de Beale. Além disso, contém a função `decodeByKeys()`, que decodifica uma mensagem a partir de um arquivo de chaves usando a cifra de Beale.
- `utils.c`: contém as definições de funções auxiliares usadas em `encode.c` e `decode.c`. arrIdxToChar() e charToArrIdx() são funções auxiliares para a conversão de índices de arrays para caracteres e vice-versa.
- `linkedlist.c`: contém as definições de funções auxiliares para a implementação de uma lista encadeada, usada para armazenar as chaves de decodificação. Ou seja, contém as definições de funções para criar, inserir, remover, imprimir em um arquivo e liberar uma lista encadeada.

## `include/`

- `encode.h`: contém as definições de funções e estruturas de dados usadas em `encode.c`.
- `decode.h`: contém as definições de funções e estruturas de dados usadas em `decode.c`.
- `utils.h`: contém as definições de funções e estruturas de dados usadas em `utils.c`.
- `linkedlist.h`: contém as definições de funções e estruturas de dados usadas em `linkedlist.c`.

# Estruturas de dados

## `linkedlist.c`

A estrutura de dados escolhida para armazenar as chaves de decodificação foi uma lista encadeada, pois a inserção de uma chave na lista é feita em tempo constante. Além disso, a lista encadeada é bem simples de ser implementada, e não há um limite para o número de elementos que podem ser armazenados na lista e, principalmente, permite a separação de blocos de memória.

# Algoritmos

## `encode.c`

#### `encodeByBook()`

1. Ler o livro e armazenar em uma lista de tamanho fixo dos caractéres ASCII imprimíveis (32 a 126). Cada elemento é uma lista encadeada de chaves de cada caractere. Ou seja, a lista de tamanho fixo é um array de listas encadeadas.

2. Para cada caractere da mensagem original, escolher uma chave aleatória da lista de chaves do caractere correspondente no livro.

3. Escrever as chaves escolhidas em um arquivo de chaves.

4. Escrever a mensagem codificada em um arquivo.

## `decode.c`

#### `decodeByKeys()`

1. Ler o arquivo de chaves e armazenar em uma string de tamanho dinâmico, tal caractere na posição cada chave. Ex.:
  
  ``` 
  a: 0 1 5 3
  b: 2 4 6
  ```

  Será armazenado como a string `"aababab"`. Assim, cada caractere da string é uma chave de decodificação, isso permite que a decodificação seja feita em tempo constante.

2. Utilizando a string de chaves, decodificar a mensagem codificada e escrever em um arquivo (-1 sendo espaço em branco e -2 uma nova linha). Ex.:

  ``` 
  0 -1 2 -2 0 1 5 6
  ```
  
  Com a string de chaves `"aababab"`, será decodificado como:

  ```  
  a b
  a a b
  ```
  
3. Escrever a mensagem decodificada em um arquivo. 

#### `decodeByBook()`

1. Ler o livro e armazenar em uma string de tamanho dinâmico, tal caractere na posição cada chave. Ex.:
  
  ``` 
  Era uma vez um rei que tinha um filho muito esperto. Um dia, o rei perguntou ao filho:
  ```

  Será armazenado como a string `"EuvurqtufmeUdorpaf"`. Caracteres especiais são ignorados.

2. Repetir o processos 2 e 3 do algoritmo `decodeByKeys()`.

# Compilação e execução

- `make`: compila o programa.
- `make test`: compila o programa e executa o programa de teste (codifica e decodifica das 2 maneiras)
- `make check`: verifica se a mensagem original coincide com ambos os arquivos decodificados (de maneira diferente) pela codificação.
- `make clean`: limpa os arquivos `.o` gerados pela compilação.
- `make purge`: limpa todos os arquivos gerados pela compilação e os arquivos de teste.

<!-- Para compilar o programa, basta executar o comando `make` na pasta raiz do projeto. Pode-se testar o programa executando o comando `make test` na pasta raiz do projeto e `make check` para verificar se a mensagem original coincide com ambos os arquivos decodificados (de maneira diferente) pela codificação. Para limpar os arquivos `.o` gerados pela compilação, basta executar o comando `make clean` na pasta raiz do projeto e `make purge` para limpar todos os arquivos gerados pela compilação e os arquivos de teste. -->

# Aluno e GRR do aluno
Marcelo Augusto Rissette Schreiber - GRR20220063
