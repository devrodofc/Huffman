# Codificação de Huffman em C

## Descrição

Este projeto implementa o algoritmo de Codificação de Huffman utilizando a linguagem C, com o objetivo de realizar compressão e descompressão de arquivos texto sem perda de dados.

A aplicação é capaz de:

* Ler arquivos texto.
* Calcular a frequência de cada caractere.
* Construir a árvore de Huffman.
* Gerar códigos binários variáveis.
* Compactar arquivos em formato `.huff`.
* Descompactar arquivos `.huff`.
* Reconstruir integralmente o conteúdo original.
* Gerenciar corretamente a memória utilizada.

---

## Sobre o Algoritmo de Huffman

A Codificação de Huffman é um algoritmo de compressão sem perdas criado por David A. Huffman em 1952.

O algoritmo atribui códigos binários menores aos caracteres mais frequentes e códigos maiores aos caracteres menos frequentes.

### Exemplo

Frequências:

| Caractere | Frequência |
| --------- | ---------- |
| A         | 50         |
| B         | 30         |
| C         | 20         |

Possível codificação:

| Caractere | Código |
| --------- | ------ |
| A         | 0      |
| B         | 10     |
| C         | 11     |

Texto original:

```text
ABC
```

Representação binária:

```text
01011
```

Dessa forma o tamanho total do arquivo é reduzido.

---

## Estrutura do Projeto

```text
huffman/
├── README.md
├── Makefile
├── book.txt
│
├── include/
│   ├── archive.h
│   ├── bitstream.h
│   ├── cli.h
│   ├── compress.h
│   ├── decompress.h
│   ├── file_io.h
│   └── tree.h
│
├── src/
│   ├── archive.c
│   ├── bitstream.c
│   ├── cli.c
│   ├── compress.c
│   ├── decompress.c
│   ├── file_io.c
│   ├── main.c
│   └── tree.c
│
├── testes/
│   ├── pequeno.txt
│   ├── medio.txt
│   ├── repetidos.txt
│   └── comum.txt
│
└── docs/
```

---

## Compilação

### GCC

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -O2 -Iinclude src/*.c -o huffman
```

### Makefile

```bash
make
```

---

## Execução

### Compactar arquivo

```bash
huffman --compactar arquivo.txt
```

Exemplo:

```bash
huffman --compactar book.txt
```

Resultado:

```text
book.huff
```

---

### Descompactar arquivo

```bash
huffman --descompactar book.huff
```

Resultado:

```text
descompactado_book.txt
```

---

## Formato do Arquivo Compactado

O arquivo `.huff` armazena:

```text
+----------------------+
| MAGIC NUMBER         |
+----------------------+
| TAMANHO ORIGINAL     |
+----------------------+
| FREQUÊNCIAS[256]     |
+----------------------+
| DADOS COMPACTADOS    |
+----------------------+
```

Essas informações permitem reconstruir exatamente a mesma árvore de Huffman durante a descompactação.

---

## Testes Realizados

Foram realizados testes com diferentes tipos de arquivos:

| Arquivo       | Objetivo             |
| ------------- | -------------------- |
| pequeno.txt   | Arquivo pequeno      |
| medio.txt     | Arquivo médio        |
| comum.txt     | Texto comum          |
| repetidos.txt | Caracteres repetidos |
| book.txt      | Arquivo grande       |

### Validação

Após cada compactação e descompactação, os arquivos foram comparados utilizando:

```bash
fc arquivo_original.txt arquivo_descompactado.txt
```

Resultado obtido:

```text
FC: nenhuma diferença encontrada
```

Com isso foi comprovado que a compressão é sem perdas.

---

## Principais Estruturas Utilizadas

### Árvore de Huffman

Responsável por armazenar os símbolos e suas frequências.

### Min Heap (Fila de Prioridade)

Utilizada para selecionar os nós de menor frequência durante a construção da árvore.

### BitStream

Permite leitura e escrita em nível de bits, aumentando a eficiência da compactação.

---

## Complexidade

### Construção da Árvore

```text
O(n log n)
```

onde:

```text
n = quantidade de símbolos distintos
```

### Geração dos Códigos

```text
O(n)
```

### Compactação

```text
O(m)
```

onde:

```text
m = tamanho do arquivo
```

### Descompactação

```text
O(m)
```

---

## Dependências

* GCC (ou outro compilador C compatível)
* CMake 4.2 ou superior (para build com CMake)
* Biblioteca padrão da linguagem C

Nenhuma biblioteca externa foi utilizada.

---

## Requisitos do Sistema

* Linux, macOS ou Windows (com MinGW/WSL)
* Compilador C (GCC, Clang, MSVC)
* Make ou CMake

---

## Instalação e Build

### Opção 1: Usando Makefile

```bash
cd huffman
make
```

### Opção 2: Usando CMake

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Opção 3: Compilação Manual com GCC

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -O2 -Iinclude src/*.c -o huffman
```

---

## Exemplos de Uso

### Compactar um arquivo

```bash
./huffman --compactar testes/pequeno.txt
```

Resultado: `pequeno.huff`

### Descompactar um arquivo

```bash
./huffman --descompactar pequeno.huff
```

Resultado: `descompactado_pequeno.txt`

### Verificar integridade (comparar original com descompactado)

```bash
# No Linux/macOS
diff testes/pequeno.txt descompactado_pequeno.txt

# No Windows
fc testes\pequeno.txt descompactado_pequeno.txt
```

---

## Testes Inclusos

O projeto inclui arquivos de teste em `testes/`:

- **pequeno.txt**: Arquivo pequeno para testes rápidos
- **medio.txt**: Arquivo de tamanho médio
- **comum.txt**: Texto com caracteres comuns
- **repetidos.txt**: Arquivo com caracteres repetidos (taxa de compressão alta)

Arquivos `.huff` já compactados estão disponíveis para testes de descompactação.

---

## Arquitetura do Código

### Módulos Principais

| Módulo | Descrição |
| ------ | --------- |
| `huffman.h/c` | Funções principais do algoritmo |
| `tree.h/c` | Estrutura e manipulação da árvore de Huffman |
| `compress.h/c` | Lógica de compactação |
| `decompress.h/c` | Lógica de descompactação |
| `archive.h/c` | Gerenciamento do formato `.huff` |
| `bitstream.h/c` | Operações com bits |
| `file_io.h/c` | Leitura e escrita de arquivos |
| `cli.h/c` | Interface de linha de comando |

---

## Análise de Compressão

### Taxa de Compressão Observada

O algoritmo de Huffman consegue taxas de compressão variáveis dependendo do tipo de arquivo:

- **Arquivos com poucos caracteres distintos**: Até 60-80% de redução
- **Texto comum**: 30-50% de redução
- **Dados aleatórios**: Pouca ou nenhuma redução

### Overhead

A presença da tabela de frequências no arquivo compactado adiciona um pequeno overhead (~1KB), que é insignificante em arquivos grandes.

---

## Limitações Conhecidas

- Tamanho máximo de arquivo: Limitado pela memória disponível
- Suporta apenas caracteres ASCII (256 símbolos)
- A compressão é otimizada para texto comum

---

## Possíveis Melhorias

- [ ] Suporte para compressão de múltiplos arquivos em um único `.huff`
- [ ] Implementação de compressão em múltiplas threads
- [ ] Suporte para símbolos Unicode
- [ ] Interface gráfica (GUI)
- [ ] Integração com arquivos ZIP/RAR

---

## Referências

- **Huffman, D. A.** (1952). "A Method for the Construction of Minimum-Redundancy Codes". Proceedings of the IRE.
- [Algoritmo de Huffman - Wikipedia](https://en.wikipedia.org/wiki/Huffman_coding)
- [Estruturas de Dados - Árvores](https://en.wikipedia.org/wiki/Binary_tree)

---

## Autor

**Rodrigo Morais Herrmann**

Projeto desenvolvido para a disciplina de Estruturas de Dados e Algoritmos.

Implementação realizada em linguagem C utilizando Codificação de Huffman para compressão sem perdas.

---

## Licença

Este projeto é fornecido como está, para fins educacionais.

---

## Contato

Para dúvidas ou sugestões sobre o projeto, consulte a documentação ou entre em contato através do repositório.
