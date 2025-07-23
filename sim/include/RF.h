#ifndef RF_H
#define RF_H

class RF {
private:
    bool registers[64][128];  // 64个寄存器，每个128位
    
public:
    RF();
    
    void write(int index, const bool data[128]);
    void read(int index, bool out[128]) const;
    void clean();
    void copy(int from, int to);
    void readPair(int r1, int r2, int r3,int r4, bool out1[128], bool out2[128], bool out3[128], bool out4[128]);
    void setBit(int reg,int BitIndex, bool val);
    bool getBit(int reg,int BitIndex) ;
    bool eq(int reg1, int reg2) const;
    bool zf(int reg) const;
    void getSlice(int reg, int start, int end, bool out[128]) const;
    void setSlice(int reg, int start, int end, const bool data[128]);
    void BitwiseAnd(int reg1, int reg2, int outReg);
    void BitwiseOr(int reg1, int reg2, int outReg);
    void BitwiseXor(int reg1, int reg2, int outReg);
    void BitwiseNot(int reg, int outReg);
    void BitwiseNand(int reg1, int reg2, int outReg);
    void BitwiseNor(int reg1, int reg2, int outReg);
    void BitwiseXnor(int reg1, int reg2, int outReg);
    void Bit_SL(int reg, int outReg);
    void Bit_SR(int reg, int outReg);
    void Bit_RF(int reg, int outReg);
    void set_ALL(int reg);
    bool cmp(int reg1, int reg2, int outReg);
    void Bit_swap(int reg1, int reg2);
    int Bit_sub(int reg1, int reg2);
    int maskAnd(int reg1, int reg2);
};

#endif // RF_H