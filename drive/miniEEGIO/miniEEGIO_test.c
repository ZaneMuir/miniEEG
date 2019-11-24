#include "stdio.h"
#include "stdlib.h"
#include "miniEEG.h"

MiniEEGChunkHeader* test_chunk_hdr(long idx) {
    MiniEEGChunkHeader* hdr = (MiniEEGChunkHeader*)malloc(sizeof(MiniEEGChunkHeader));
    hdr -> chunk_idx = idx;
    hdr -> timestamp = 12.334;
    hdr -> frequency = 2000;
    hdr -> channel_num = 6;
    hdr -> chunk_size = 512;
    return hdr;
}

void test_file_hdr(MiniEEGHeader* hdr) {
    hdr -> magic_number = 0x1f002f00;
    return;
}

FILE* create_record_file(const char* filename) {
    FILE* rfile = fopen(filename, "w+");
    unsigned char _empty_hdr[512] = {0};
    fwrite(&_empty_hdr, sizeof(_empty_hdr), 1, rfile);
    return rfile;
}

void append_record_chunk(FILE* rfile, MiniEEGChunkHeader* chunk_hdr, short* data, size_t len){
    fwrite(chunk_hdr, sizeof(MiniEEGChunkHeader), 1, rfile);
    fwrite(data, len, 1, rfile);
    return;
}

void close_record_file(FILE* rfile, const MiniEEGHeader* hdr) {
    rewind(rfile);
    fwrite(hdr, sizeof(MiniEEGHeader), 1, rfile);
    fclose(rfile);
    return;
}