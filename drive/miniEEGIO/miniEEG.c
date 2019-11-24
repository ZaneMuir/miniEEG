#include "stdio.h"
#include "stdlib.h"
#include "miniEEG.h"

// writer
FILE* create_record_file(const char* filename) {
    FILE* rfile = fopen(filename, "w+");
    unsigned char _empty_hdr[512] = {0};
    fwrite(&_empty_hdr, sizeof(_empty_hdr), 1, rfile);
    return rfile;
}

void append_record_chunk(FILE* rfile, const MiniEEGChunkHeader* chunk_hdr, const short* data, const size_t len){
    fwrite(chunk_hdr, sizeof(MiniEEGChunkHeader), 1, rfile);
    fwrite(data, sizeof(short), len, rfile);
    return;
}

void ending_record_file(FILE* rfile, const MiniEEGHeader* hdr) {
    //fseek(rfile, 0, SEEK_SET);
    rewind(rfile);
    fwrite(hdr, sizeof(MiniEEGHeader), 1, rfile);
    fclose(rfile);
    return;
}

// reader
MiniEEGHeader* read_record_header(const char* filename) {
    FILE* rfile = fopen(filename, "r");
    MiniEEGHeader* hdr = (MiniEEGHeader*)malloc(sizeof(MiniEEGHeader));
    fread(hdr, sizeof(MiniEEGHeader), 1, rfile);
    fclose(rfile);
    return hdr;
}

FILE* open_record_file(const char* filename) {
    FILE* rfile = fopen(filename, "r");
    return rfile;
}

void close_record_file(FILE* rfile) {
    fclose(rfile);
    return;
}

MiniEEGHeader* load_record_header(FILE* rfile) {
    fseek(rfile, 0, SEEK_SET);
    MiniEEGHeader* hdr = (MiniEEGHeader*)malloc(sizeof(MiniEEGHeader));
    fread(hdr, sizeof(MiniEEGHeader), 1, rfile);
    return hdr;
}

short* load_data(FILE* rfile) {
    MiniEEGHeader* hdr = load_record_header(rfile);
    MiniEEGChunkHeader* chunk_hdr = (MiniEEGChunkHeader*)malloc(sizeof(MiniEEGChunkHeader));
    
    size_t chunk_len = (size_t)(hdr -> channel_num * hdr -> chunk_size);
    size_t total_len = chunk_len * hdr -> chunk_num;
    
    short* data = (short*)malloc(sizeof(short)*total_len);
    for (size_t i = 0; i < hdr -> chunk_num - 1; i++) {
        fread(chunk_hdr, sizeof(MiniEEGChunkHeader), 1, rfile);
        fread(data+chunk_len*i, sizeof(short), chunk_len, rfile);
    }
    
    free(hdr);
    free(chunk_hdr);
    return data;
}

MiniEEGChunkHeader* load_chunk_header(FILE* rfile, long int pos) {
    fseek(rfile, pos, SEEK_SET);
    MiniEEGChunkHeader* hdr = (MiniEEGChunkHeader*)malloc(sizeof(MiniEEGChunkHeader));
    fread(hdr, sizeof(MiniEEGChunkHeader), 1, rfile);
    return hdr;
}

short* load_chunk_data(FILE* rfile, long int pos, size_t len) {
    fseek(rfile, pos, SEEK_SET);
    short* data = (short*)malloc(sizeof(short) * len);
    fread(data, sizeof(short), len, rfile);
    return data;
}

int iseof(FILE* rfile) {
    return feof(rfile);
}

short* next_chunk_data(FILE* rfile) {
    MiniEEGChunkHeader* hdr = (MiniEEGChunkHeader*)malloc(sizeof(MiniEEGChunkHeader));
    fread(hdr, sizeof(MiniEEGChunkHeader), 1, rfile);
    
    size_t len = (size_t)(hdr->channel_num) * (size_t)(hdr -> chunk_size);
    
    short* data = (short*)malloc(sizeof(short) * len);
    fread(data, sizeof(short), len, rfile);
    free(hdr);
    return data;
}