#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../include/file_io.h"

uint64_t get_file_size(FILE *file)
{
    if (!file)
    {
        return 0;
    }

    long current_pos = ftell(file);

    fseek(file, 0, SEEK_END);

    long size = ftell(file);

    fseek(file, current_pos, SEEK_SET);

    if (size < 0)
    {
        return 0;
    }

    return (uint64_t)size;
}


unsigned char *read_file(
    const char *filename,
    uint64_t *size)
{
    FILE *file =
        fopen(filename, "rb");

    if (!file)
    {
        return NULL;
    }

    uint64_t file_size =
        get_file_size(file);

    if (file_size == 0)
    {
        fclose(file);
        return NULL;
    }

    rewind(file);

    unsigned char *buffer =
        (unsigned char *)malloc(file_size);

    if (!buffer)
    {
        fclose(file);
        return NULL;
    }

    size_t bytes_read =
        fread(
            buffer,
            1,
            file_size,
            file);

    fclose(file);

    if (bytes_read != file_size)
    {
        free(buffer);
        return NULL;
    }

    if (size)
    {
        *size = file_size;
    }

    return buffer;
}


int write_file(
    const char *filename,
    const unsigned char *data,
    uint64_t size)
{
    FILE *file =
        fopen(filename, "wb");

    if (!file)
    {
        return 0;
    }

    size_t bytes_written =
        fwrite(
            data,
            1,
            size,
            file);

    fclose(file);

    return bytes_written == size;
}