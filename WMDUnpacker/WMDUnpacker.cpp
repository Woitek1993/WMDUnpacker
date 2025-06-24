#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>

#include "tga.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"
#include "WMDFormat.h"

static void print_usage(const char* progname) {
    printf(
        "Usage:\n"
        "  %s <input.bkw> <output.tga>\n\n"
        "  <input.bkw>   Path to the Worms WMD .bkw file to read\n"
        "  <output.tga>  Path to write the uncompressed 32-bit TGA image\n",
        progname
    );
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Error: wrong number of arguments.\n");
        print_usage(argv[0]);
        return 1;
    }

    const char* inputPath = argv[1];
    const char* outputPath = argv[2];

    //check if input exists
    {
        std::ifstream check(inputPath, std::ios::binary);
        if (!check) {
            fprintf(stderr, "Error: input file not found: \"%s\"\n", inputPath);
            print_usage(argv[0]);
            return 1;
        }
    }

    //open reader
    BinaryFileReader reader;
    if (reader.open(inputPath) != 0) {
        fprintf(stderr, "Error: could not open \"%s\"\n", inputPath);
        return 1;
    }

    //read BKW header
    BKW_HEADER header;
    if (reader.read_bytes(&header, sizeof(header)) != 0) {
        fprintf(stderr, "Error: failed to read BKW_HEADER\n");
        reader.close();
        return 1;
    }

    //compute tile geometry
    const uint32_t BLOCK_W = header.vars[80];
    const uint32_t BLOCK_H = header.vars[80];
    const uint32_t BLOCK_SIZE = BLOCK_W * BLOCK_H * 4;
    const uint32_t blocksX = header.vars[18] / BLOCK_W;
    const uint32_t blocksY = header.vars[19] / BLOCK_H;
    const uint32_t block_count = blocksX * blocksY;
    const uint32_t BLOCKS_PER_ROW = blocksX;

    const size_t rows = (block_count + BLOCKS_PER_ROW - 1) / BLOCKS_PER_ROW;
    const size_t tilesPerRow = std::min<size_t>(block_count, BLOCKS_PER_ROW);
    const size_t totalShift = (tilesPerRow > 0 ? (tilesPerRow - 1) : 0) * 2;
    const size_t final_w = tilesPerRow * BLOCK_W - totalShift;
    const size_t final_h = rows * BLOCK_H;

    tga_header th = {};
    th.id_length = 0;
    th.map_type = 0;
    th.image_type = 2;
    th.map_first_entry = 0;
    th.map_length = 0;
    th.map_entry_size = 0;
    th.image_x_origin = 0;
    th.image_y_origin = 0;
    th.image_width = static_cast<uint16_t>(final_w);
    th.image_height = static_cast<uint16_t>(final_h);
    th.pixel_depth = 32;
    th.image_descriptor = 8;

    //read raw pixels
    const size_t rawSize = header.vars[81];
    char* allpixels = new char[rawSize];
    if (reader.read_bytes(allpixels, rawSize) != 0) {
        fprintf(stderr, "Error: failed to read pixel data\n");
        delete[] allpixels;
        reader.close();
        return 1;
    }
    reader.close();

    //allocate canvas
    const size_t canvasSize = final_w * final_h * 4;
    char* buffer = new char[canvasSize];
    std::memset(buffer, 0x00, canvasSize);

    //blit each tile with 2px left-shift per column
    for (size_t i = 0; i < block_count; ++i) {
        size_t src_off = i * BLOCK_SIZE;
        size_t col = i % BLOCKS_PER_ROW;
        size_t row = i / BLOCKS_PER_ROW;

        size_t dst_x = col * BLOCK_W - col * 2;
        size_t dst_y = row * BLOCK_H;

        for (size_t y = 0; y < BLOCK_H; ++y) {
            size_t src_line = src_off + y * (BLOCK_W * 4);
            size_t dst_line = ((dst_y + y) * final_w + dst_x) * 4;
            std::memcpy(&buffer[dst_line],
                &allpixels[src_line],
                BLOCK_W * 4);
        }
    }
    delete[] allpixels;

    //swap R with B channels in-place
    for (size_t i = 0; i < canvasSize; i += 4) {
        unsigned char tmp = buffer[i];
        buffer[i] = buffer[i + 2];
        buffer[i + 2] = tmp;
    }

    //write out TGA
    BinaryFileWriter writer;
    if (writer.bfw_open(outputPath) != 0) {
        fprintf(stderr, "Error: could not open \"%s\" for writing\n", outputPath);
        delete[] buffer;
        return 1;
    }

    writer.bfw_write_bytes(&th, sizeof(th));
    writer.bfw_write_bytes(buffer, canvasSize);
    writer.bfw_close();
    delete[] buffer;

    printf("File \"%s\" was successfully written\n",outputPath);
    return 0;
}
