#ifndef MENORY_H
#define MEMORY_H

class Mem {
    private:
        bool mem[128][128];
    
    public:
        Mem();
    
        void write(int addr, const bool data[128]);
        void read(int addr, bool out[128]) const;
        void setBit(int addr, int bitIndex, bool val);
        bool getBit(int addr, int bitIndex) const;
        void wirteblock(int addr, const bool data[128][128]);
        void readblock(int addr, bool out[128][128]) const;

        void wirte_8(int addr, const bool data[8]);
        void read_8(int addr, bool out[8]) const;
    
        void wirte_16(int addr, const bool data[16]);
        void read_16(int addr, bool out[16]) const;

        void wirte_32(int addr, const bool data[32]);
        void read_32(int addr, bool out[32]) const;

        void wirte_64(int addr, const bool data[64]);
        void read_64(int addr, bool out[64]) const;

        void write_linear(int bit_addr, const bool* data, int len);
        void read_linear(int bit_addr, bool* out, int len) const;

        void clear();
    };

#endif // MEMORY_H