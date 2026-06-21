#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../include/compress.h"
#include "../include/tree.h"
#include "../include/file_io.h"
#include "../include/archive.h"
#include "../include/bitstream.h"

static char *generate_output_name(
    const char *input_filename)
{
    size_t len = strlen(input_filename);

    char *output =
        (char *)malloc(len + 6);

    if (!output)
    {
        return NULL;
    }

    strcpy(output, input_filename);

    char *dot = strrchr(output, '.');

    if (dot)
    {
        *dot = '\0';
    }

    strcat(output, ".huff");

    return output;
}


static void count_frequencies(
    const unsigned char *data,
    uint64_t size,
    uint64_t frequencies[MAX_SYMBOLS])
{
    memset(
        frequencies,
        0,
        sizeof(uint64_t) * MAX_SYMBOLS);

    for (uint64_t i = 0; i < size; i++)
    {
        frequencies[data[i]]++;
    }
}

int compress_file(
    const char *input_filename)
{
    uint64_t original_size = 0;

    unsigned char *data =
        read_file(
            input_filename,
            &original_size);

    if (!data)
    {
        fprintf(
            stderr,
            "Erro ao ler arquivo: %s\n",
            input_filename);

        return 0;
    }

    uint64_t frequencies[MAX_SYMBOLS];

    count_frequencies(
        data,
        original_size,
        frequencies);

    HuffmanNode *root =
        build_huffman_tree(
            frequencies);

    if (!root)
    {
        free(data);
        return 0;
    }

    HuffmanCode table[MAX_SYMBOLS];

    memset(
        table,
        0,
        sizeof(table));

    char buffer[MAX_CODE_LENGTH];

    generate_codes(
        root,
        table,
        buffer,
        0);

    char *output_filename =
        generate_output_name(
            input_filename);

    if (!output_filename)
    {
        free_tree(root);
        free(data);
        return 0;
    }

    FILE *output =
        fopen(
            output_filename,
            "wb");

    if (!output)
    {
        free(output_filename);
        free_tree(root);
        free(data);
        return 0;
    }

    HuffmanHeader header;

    header.magic = HUFF_MAGIC;
    header.original_size = original_size;

    memcpy(
        header.frequencies,
        frequencies,
        sizeof(frequencies));

    if (!write_header(
            output,
            &header))
    {
        fclose(output);

        free(output_filename);
        free_tree(root);
        free(data);

        return 0;
    }

    BitWriter writer;

    bitwriter_init(
        &writer,
        output);

    for (uint64_t i = 0; i < original_size; i++)
    {
        bitwriter_write_code(
            &writer,
            table[data[i]].code);
    }

    bitwriter_flush(
        &writer);

    fclose(output);

    printf(
        "Arquivo compactado gerado: %s\n",
        output_filename);

    free(output_filename);
    free_tree(root);
    free(data);

    return 1;
}