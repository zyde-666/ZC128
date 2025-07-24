#include"../include/InstructionSet.h"

int bitsToInt(const bool* bits,int start,int len) {
    int value = 0;
    for (int i = 0; i < len; ++i) {
        if (bits[start + i]) {
            value |= (1 << i);
        }
    }
    return value;
}

void intToBits(int value, bool* bits, int start, int len) {
    for (int i = 0; i < len; ++i) {
        bits[start + i] = (value >>i) & 1;
    }
}

Instruction decode(const bool inst[128]){
    Instruction i;
    i.op =static_cast<Opcode>(bitsToInt(inst,0,8));
    i.dst = bitsToInt(inst, 8, 6);
    i.src1 = bitsToInt(inst, 14, 6);
    i.src2 = bitsToInt(inst, 20, 6);
    i.imm = bitsToInt(inst, 26, 102);
    return i;
}
void encode(const Instruction& ins, bool out[128]) {
    for (int i = 0; i < 128; ++i) out[i] = false; // 初始化
    intToBits(ins.op, out, 0, 8);
    intToBits(ins.dst, out, 8, 6);
    intToBits(ins.src1, out, 14, 6);
    intToBits(ins.src2, out, 20, 6);
    intToBits(ins.imm, out, 26, 32);
}