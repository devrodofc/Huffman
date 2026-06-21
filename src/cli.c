#include <stdio.h>
#include <string.h>

#include "../include/cli.h"
#include "../include/compress.h"
#include "../include/decompress.h"

static void print_usage(const char *program_name)
{
    printf("\n");
    printf("Uso:\n");
    printf("  %s --compactar <arquivo.txt>\n", program_name);
    printf("  %s --descompactar <arquivo.huff>\n", program_name);
    printf("\n");
}

int process_cli(
    int argc,
    char *argv[])
{
    if (argc != 3)
    {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--compactar") == 0)
    {
        if (!compress_file(argv[2]))
        {
            fprintf(stderr,
                    "Falha durante a compactacao.\n");
            return 1;
        }

        return 0;
    }

    if (strcmp(argv[1], "--descompactar") == 0)
    {
        if (!decompress_file(argv[2]))
        {
            fprintf(stderr,
                    "Falha durante a descompactacao.\n");
            return 1;
        }

        return 0;
    }

    fprintf(stderr,
            "Comando invalido.\n");

    print_usage(argv[0]);

    return 1;
}