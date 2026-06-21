#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdint.h>


unsigned char *read_file(
    const char *filename,
    uint64_t *size
);


int write_file(
    const char *filename,
    const unsigned char *data,
    uint64_t size
);


uint64_t get_file_size(
    FILE *file
);

#endif