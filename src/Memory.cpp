#include "../include/Memory.h"

Mem::Mem() {
    clear();
}

void Mem::clear() {
    for (int i = 0; i < 128; ++i)
        for (int j = 0; j < 128; ++j)
            mem[i][j] = false;
}

void Mem::write(int addr, const bool data[128]) {
    if (addr < 0 || addr >= 128) return;
    for (int i = 0; i < 128; ++i)
        mem[addr][i] = data[i];
}

void Mem::read(int addr, bool out[128]) const {
    if (addr < 0 || addr >= 128) return;
    for (int i = 0; i < 128; ++i)
        out[i] = mem[addr][i];
}

void Mem::setBit(int addr, int bitIndex, bool val) {
    if (addr < 0 || addr >= 128 || bitIndex < 0 || bitIndex >= 128) return;
    mem[addr][bitIndex] = val;
}

bool Mem::getBit(int addr, int bitIndex) const {
    if (addr < 0 || addr >= 128 || bitIndex < 0 || bitIndex >= 128) return false;
    return mem[addr][bitIndex];
}

void Mem::wirteblock(int addr, const bool data[128][128]) {
    if (addr < 0 || addr + 128 >= 128) return;
    for (int i = 0; i < 128; ++i)
        for (int j = 0; j < 128; ++j)
            mem[addr+i][j] = data[i][j];
}

void Mem::readblock(int addr, bool out[128][128]) const {
    if (addr < 0 || addr + 128 >= 128) return;
    for (int i = 0; i < 128; ++i)
        for (int j = 0; j < 128; ++j)
            out[i][j] = mem[addr+i][j];
}

void Mem::wirte_8(int addr, const bool data[8]) {
    write_linear(addr, data, 8);
}

void Mem::read_8(int addr, bool out[8]) const {
    read_linear(addr, out, 8);
}

void Mem::wirte_16(int addr, const bool data[16]) {
    write_linear(addr, data, 16);
}

void Mem::read_16(int addr, bool out[16]) const {
    read_linear(addr, out, 16);
}

void Mem::wirte_32(int addr, const bool data[32]) {
    write_linear(addr, data, 32);
}

void Mem::read_32(int addr, bool out[32]) const {
    read_linear(addr, out, 32);
}

void Mem::wirte_64(int addr, const bool data[64]) {
    write_linear(addr, data, 64);
}

void Mem::read_64(int addr, bool out[64]) const {
    read_linear(addr, out, 64);
}

void Mem::write_linear(int bit_addr, const bool* data, int len) {
    for (int i = 0; i < len; ++i) {
        int bitIndex = (bit_addr + i) % 128;
        int wordAddr = (bit_addr + i) / 128;
        if (wordAddr >= 128) return; // 防越界
        mem[wordAddr][bitIndex] = data[i];
    }
}

void Mem::read_linear(int bit_addr, bool* out, int len) const {
    for (int i = 0; i < len; ++i) {
        int bitIndex = (bit_addr + i) % 128;
        int wordAddr = (bit_addr + i) / 128;
        if (wordAddr >= 128) return;
        out[i] = mem[wordAddr][bitIndex];
    }
}



