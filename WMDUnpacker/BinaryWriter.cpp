#include "BinaryWriter.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

BinaryFileWriter::BinaryFileWriter()
{
    m_file = NULL;
}

BinaryFileWriter::~BinaryFileWriter() {
    bfw_close();
}

int BinaryFileWriter::bfw_open(const char* path) {
    if (m_file) {
        std::fclose(m_file);
        m_file = NULL;
    }
    std::remove(path);
    m_file = std::fopen(path, "wb");
    return m_file ? 0 : -1;
}

void BinaryFileWriter::bfw_close() {
    if (m_file) {
        std::fclose(m_file);
        m_file = NULL;
    }
}

long BinaryFileWriter::bfw_tell() {
    return m_file ? std::ftell(m_file) : -1;
}

int BinaryFileWriter::bfw_seek(long offset) {
    return (m_file && std::fseek(m_file, offset, SEEK_SET) == 0) ? 0 : -1;
}

int BinaryFileWriter::bfw_write_bytes(const void* buffer, size_t count) {
    if (!m_file || !buffer) return -1;
    size_t written = std::fwrite(buffer, 1, count, m_file);
    return (written == count) ? 0 : -1;
}

int BinaryFileWriter::bfw_write_int8(int8_t value) { return bfw_write_bytes(&value, sizeof(value)); }
int BinaryFileWriter::bfw_write_uint8(uint8_t value) { return bfw_write_bytes(&value, sizeof(value)); }
int BinaryFileWriter::bfw_write_int16(int16_t v) { return bfw_write_bytes(&v, sizeof(v)); }
int BinaryFileWriter::bfw_write_uint16(uint16_t v) { return bfw_write_bytes(&v, sizeof(v)); }
int BinaryFileWriter::bfw_write_int32(int32_t v) { return bfw_write_bytes(&v, sizeof(v)); }
int BinaryFileWriter::bfw_write_uint32(uint32_t v) { return bfw_write_bytes(&v, sizeof(v)); }
int BinaryFileWriter::bfw_write_int64(int64_t v) { return bfw_write_bytes(&v, sizeof(v)); }
int BinaryFileWriter::bfw_write_uint64(uint64_t v) { return bfw_write_bytes(&v, sizeof(v)); }
int BinaryFileWriter::bfw_write_float(float v) { return bfw_write_bytes(&v, sizeof(v)); }
int BinaryFileWriter::bfw_write_double(double v) { return bfw_write_bytes(&v, sizeof(v)); }
