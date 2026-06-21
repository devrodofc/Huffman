#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    FILE *file;

    unsigned char buffer;

    int bit_count;

} BitWriter;


typedef struct
{
    FILE *file;

    unsigned char buffer;

    int bit_count;

} BitReader;

void bitwriter_init(
    BitWriter *writer,
    FILE *file
);


void bitwriter_write_bit(
    BitWriter *writer,
    int bit
);

void bitwriter_write_code(
    BitWriter *writer,
    const char *code
);

void bitwriter_flush(
    BitWriter *writer
);


void bitreader_init(
    BitReader *reader,
    FILE *file
);


int bitreader_read_bit(
    BitReader *reader
);

#endif