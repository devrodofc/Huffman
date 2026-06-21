cmake_minimum_required(VERSION 4.2)
project(huffman C)

set(CMAKE_C_STANDARD 11)

add_executable(huffman src/main.c
        include/huffman.h
        include/cli.h
        include/file_io.h
        include/bitstream.h
        include/tree.h
        include/archive.h
        include/compress.h
        include/decompress.h
        src/cli.c
        src/file_io.c
        src/tree.c
        src/archive.c
        src/bitstream.c
        src/compress.c
        src/decompress.c
)

