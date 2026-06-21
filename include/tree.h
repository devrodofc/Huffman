#ifndef TREE_H
#define TREE_H

#include <stdint.h>

#define MAX_SYMBOLS 256
#define MAX_CODE_LENGTH 512

typedef struct HuffmanNode
{
    unsigned char symbol;
    uint64_t frequency;

    struct HuffmanNode *left;
    struct HuffmanNode *right;

} HuffmanNode;

typedef struct
{
    char code[MAX_CODE_LENGTH];

} HuffmanCode;

HuffmanNode *create_node(
    unsigned char symbol,
    uint64_t frequency
);

void free_tree(
    HuffmanNode *root
);

int is_leaf(
    HuffmanNode *node
);

HuffmanNode *build_huffman_tree(
    uint64_t frequencies[MAX_SYMBOLS]
);

void generate_codes(
    HuffmanNode *root,
    HuffmanCode table[MAX_SYMBOLS],
    char *buffer,
    int depth
);

#endif