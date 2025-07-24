#ifndef CACHE_H
#define CACHE_H

#include "../include/Memory.h"

struct CacheLine {
    bool valid;
    bool dirty;
    int tag;
    bool data[128];

    CacheLine() : valid(false), dirty(false), tag(0) {
        for (int i = 0; i < 128; ++i) data[i] = false;
    }
};

class Cache {
    private:
        static const int NUM_LINES = 32;
        CacheLine lines[NUM_LINES];
    
    public:
        void read(int addr, bool out[128], Mem& memory);
        void write(int addr, const bool data[128], Mem& memory);
        void flush(Mem& memory);
    };
#endif // CACHE_H