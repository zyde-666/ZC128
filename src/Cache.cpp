#include "../include/Cache.h"
#include "../include/Memory.h"

void Cache::read(int addr, bool out[128], Mem& memory) {
    int lineIndex = (addr / 128) % NUM_LINES;
    int tag = addr / (128 * NUM_LINES);

    if (lines[lineIndex].valid && lines[lineIndex].tag == tag) {
        for (int i = 0; i < 128; ++i) {
            out[i] = lines[lineIndex].data[i];
        }
    } else {
        memory.read(addr, out);
        lines[lineIndex].valid = true;
        lines[lineIndex].dirty = false;
        lines[lineIndex].tag = tag;
        for (int i = 0; i < 128; ++i) {
            lines[lineIndex].data[i] = out[i];
        }
    }
}

void Cache::write(int addr, const bool data[128], Mem& memory) {
    int lineIndex = (addr / 128) % NUM_LINES;
    int tag = addr / (128 * NUM_LINES);

    if (lines[lineIndex].valid && lines[lineIndex].tag == tag) {
        for (int i = 0; i < 128; ++i) {
            lines[lineIndex].data[i] = data[i];
        }
        lines[lineIndex].dirty = true;
    } else {
        memory.write(addr, data);
        lines[lineIndex].valid = true;
        lines[lineIndex].dirty = false;
        lines[lineIndex].tag = tag;
        for (int i = 0; i < 128; ++i) {
            lines[lineIndex].data[i] = data[i];
        }
    }
}

void Cache::flush(Mem& memory) {
    for (int i = 0; i < NUM_LINES; ++i) {
        if (lines[i].valid && lines[i].dirty) {
            int addr = (lines[i].tag * NUM_LINES + i) * 128;
            memory.write(addr, lines[i].data);
            lines[i].dirty = false;
        }
    }
}

