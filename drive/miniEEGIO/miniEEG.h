
typedef struct MiniEEGHeader {
    unsigned int magic_number; // 4 bytes
    
    // datetime created , 12 bytes
    short year;
    short month;
    short day;
    short hour;
    short minute;
    short second;
    
    // meta info, 16 bytes
    int frequency; // 4 bytes
    short channel_num; // 2 bytes
    short chunk_size; // 2 bytes
    unsigned long chunk_num; // 8 bytes
    
    // reserve 512 - 28
    unsigned char _reserve[480];
    
} MiniEEGHeader; // 512 bytes

typedef struct MiniEEGChunkHeader {
    // meta info, 24 bytes
    long chunk_idx; // 8 bytes
    double timestamp; // 8 bytes
    int frequency; // 4 bytes
    short channel_num; // 2 bytes
    short chunk_size; // 2 bytes
    
    // reserve
    unsigned char _reserve[104];
} MiniEEGChunkHeader; // 128 bytes

// FILE* create_record_file(const char* filename);
// void append_record_chunk(const FILE* rfile, const MiniEEGChunkHeader* chunk_hdr, const short* data, const size_t len);
// void close_record_file(const FILE* rfile, const MiniEEGHeader* hdr);