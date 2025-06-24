// BinaryFileWriter.h
#ifndef BINARY_FILE_WRITER_H
#define BINARY_FILE_WRITER_H

#include <cstdint>
#include <cstdio>
#include <string>

class BinaryFileWriter 
{
public:
    BinaryFileWriter();
    ~BinaryFileWriter();

    int bfw_open(const char* path);
    void bfw_close();
    long bfw_tell();
    int bfw_seek(long offset);
    int bfw_write_bytes(const void* buffer, size_t count);
    int bfw_write_int8(int8_t value);
    int bfw_write_uint8(uint8_t value);
    int bfw_write_int16(int16_t value);
    int bfw_write_uint16(uint16_t value);
    int bfw_write_int32(int32_t value);
    int bfw_write_uint32(uint32_t value);
    int bfw_write_int64(int64_t value);
    int bfw_write_uint64(uint64_t value);
    int bfw_write_float(float value);
    int bfw_write_double(double value);

private:
    FILE* m_file;
};

#endif // BINARY_FILE_WRITER_H