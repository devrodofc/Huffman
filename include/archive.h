#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <stdio.h>
#include <stdint.h>

#include "tree.h"

#define HUFF_MAGIC 0x48554646

typedef struct
{
    uint32_t magic;

    uint64_t original_size;

    uint64_t frequencies[MAX_SYMBOLS];

} HuffmanHeader;


int write_header(
    FILE *file,
    const HuffmanHeader *header
);

int read_header(
    FILE *file,
    HuffmanHeader *header
);


HuffmanNode *rebuild_tree_from_header(
    const HuffmanHeader *header
);

#endif