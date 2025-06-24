
#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

class BinaryFileReader
{
public:
    BinaryFileReader();
    ~BinaryFileReader();

    int open(const char* path);
    void close();
    long size();
    long tell();
    int seek(long offset);
    int read_bytes(void* buffer, size_t count);
    int read_int8(int8_t* out);
    int read_uint8(uint8_t* out);
    int read_int16(int16_t* out);
    int read_uint16(uint16_t* out);
    int read_int32(int32_t* out);
    int read_uint32(uint32_t* out);
    int read_int64(int64_t* out);
    int read_uint64(uint64_t* out);
    int read_float(float* out);
    int read_double(double* out);

private:
    FILE* m_file;
    long  m_size;
};

#endif