#include <stdio.h>

#include "../include/bitstream.h"

void bitwriter_init(
    BitWriter *writer,
    FILE *file)
{
    writer->file = file;
    writer->buffer = 0;
    writer->bit_count = 0;
}

void bitwriter_write_bit(
    BitWriter *writer,
    int bit)
{
    writer->buffer <<= 1;

    if (bit)
    {
        writer->buffer |= 1;
    }

    writer->bit_count++;

    if (writer->bit_count == 8)
    {
        fwrite(
            &writer->buffer,
            sizeof(unsigned char),
            1,
            writer->file);

        writer->buffer = 0;
        writer->bit_count = 0;
    }
}

void bitwriter_write_code(
    BitWriter *writer,
    const char *code)
{
    while (*code)
    {
        bitwriter_write_bit(
            writer,
            (*code == '1'));

        code++;
    }
}

void bitwriter_flush(
    BitWriter *writer)
{
    if (writer->bit_count == 0)
    {
        return;
    }

    writer->buffer <<= (8 - writer->bit_count);

    fwrite(
        &writer->buffer,
        sizeof(unsigned char),
        1,
        writer->file);

    writer->buffer = 0;
    writer->bit_count = 0;
}


void bitreader_init(
    BitReader *reader,
    FILE *file)
{
    reader->file = file;
    reader->buffer = 0;
    reader->bit_count = 0;
}

int bitreader_read_bit(
    BitReader *reader)
{
    if (reader->bit_count == 0)
    {
        size_t bytes_read =
            fread(
                &reader->buffer,
                sizeof(unsigned char),
                1,
                reader->file);

        if (bytes_read != 1)
        {
            return -1;
        }

        reader->bit_count = 8;
    }

    int bit =
        (reader->buffer & 0x80) ? 1 : 0;

    reader->buffer <<= 1;

    reader->bit_count--;

    return bit;
}