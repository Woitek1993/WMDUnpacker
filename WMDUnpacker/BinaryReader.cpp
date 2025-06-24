#include "BinaryReader.h"
#include <stdio.h> 
#include <stdint.h> 

BinaryFileReader::BinaryFileReader()
{
    m_file = 0;
    m_size = 0;
}

BinaryFileReader::~BinaryFileReader()
{
    close();
}

int BinaryFileReader::open(const char* path)
{
    if (m_file != NULL) {
        fclose(m_file);
        m_file = NULL;
        m_size = 0;
    }

    m_file = fopen(path, "rb");
    if (m_file == NULL) {
        return -1;
    }

    if (fseek(m_file, 0, SEEK_END) != 0) {
        fclose(m_file);
        m_file = NULL;
        return -1;
    }
    m_size = ftell(m_file);
    rewind(m_file);

    return 0;
}

void BinaryFileReader::close()
{
    if (m_file != NULL) {
        fclose(m_file);
        m_file = NULL;
    }
    m_size = 0;
}

long BinaryFileReader::size()
{
    return m_size;
}

long BinaryFileReader::tell()
{
    if (m_file == NULL) {
        return -1;
    }
    return ftell(m_file);
}

int BinaryFileReader::seek(long offset)
{
    if (m_file == NULL) {
        return -1;
    }
    return (fseek(m_file, offset, SEEK_SET) == 0) ? 0 : -1;
}

int BinaryFileReader::read_bytes(void* buffer, size_t count)
{
    if (m_file == NULL || buffer == NULL) {
        return -1;
    }
    size_t read = fread(buffer, 1, count, m_file);
    return (read == count) ? 0 : -1;
}

int BinaryFileReader::read_int8(int8_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_uint8(uint8_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_int16(int16_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_uint16(uint16_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_int32(int32_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_uint32(uint32_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_int64(int64_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_uint64(uint64_t* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_float(float* out)
{
    return read_bytes(out, sizeof(*out));
}

int BinaryFileReader::read_double(double* out)
{
    return read_bytes(out, sizeof(*out));
}
