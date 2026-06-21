#include <stdio.h>
#include <stdlib.h>

#include "../include/archive.h"
#include "../include/tree.h"

int write_header(
    FILE *file,
    const HuffmanHeader *header)
{
    if (!file || !header)
    {
        return 0;
    }

    if (fwrite(
            header,
            sizeof(HuffmanHeader),
            1,
            file) != 1)
    {
        return 0;
    }

    return 1;
}

int read_header(
    FILE *file,
    HuffmanHeader *header)
{
    if (!file || !header)
    {
        return 0;
    }

    if (fread(
            header,
            sizeof(HuffmanHeader),
            1,
            file) != 1)
    {
        return 0;
    }

    if (header->magic != HUFF_MAGIC)
    {
        return 0;
    }

    return 1;
}

HuffmanNode *rebuild_tree_from_header(
    const HuffmanHeader *header)
{
    if (!header)
    {
        return NULL;
    }

    return build_huffman_tree(
        (uint64_t *)header->frequencies);
}