#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../include/decompress.h"
#include "../include/archive.h"
#include "../include/tree.h"
#include "../include/bitstream.h"

static char *generate_output_name(
    const char *input_filename)
{
    const char *filename =
        strrchr(input_filename, '\\');

    if (!filename)
    {
        filename =
            strrchr(input_filename, '/');
    }

    if (filename)
    {
        filename++;
    }
    else
    {
        filename = input_filename;
    }

    const char *prefix =
        "descompactado_";

    size_t len =
        strlen(prefix) +
        strlen(filename) +
        16;

    char *output =
        (char *)malloc(len);

    if (!output)
    {
        return NULL;
    }

    strcpy(output, prefix);
    strcat(output, filename);

    char *dot =
        strrchr(output, '.');

    if (dot)
    {
        strcpy(dot, ".txt");
    }

    return output;
}


int decompress_file(
    const char *input_filename)
{
    FILE *input =
        fopen(
            input_filename,
            "rb");

    if (!input)
    {
        fprintf(
            stderr,
            "Erro ao abrir arquivo: %s\n",
            input_filename);

        return 0;
    }

    HuffmanHeader header;

    if (!read_header(
            input,
            &header))
    {
        fprintf(
            stderr,
            "Arquivo .huff inválido.\n");

        fclose(input);

        return 0;
    }

    HuffmanNode *root =
        rebuild_tree_from_header(
            &header);

    if (!root)
    {
        fclose(input);
        return 0;
    }

    char *output_filename =
        generate_output_name(
            input_filename);

    if (!output_filename)
    {
        free_tree(root);
        fclose(input);

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
        fclose(input);

        return 0;
    }

    BitReader reader;

    bitreader_init(
        &reader,
        input);

    uint64_t produced =
        0;

    while (produced <
           header.original_size)
    {
        HuffmanNode *current =
            root;

        while (!is_leaf(current))
        {
            int bit =
                bitreader_read_bit(
                    &reader);

            if (bit < 0)
            {
                fclose(output);
                fclose(input);

                free(output_filename);
                free_tree(root);

                return 0;
            }

            if (bit == 0)
            {
                current =
                    current->left;
            }
            else
            {
                current =
                    current->right;
            }
        }

        fputc(
            current->symbol,
            output);

        produced++;
    }

    fclose(output);
    fclose(input);

    printf(
        "Arquivo descompactado gerado: %s\n",
        output_filename);

    free(output_filename);
    free_tree(root);

    return 1;
}