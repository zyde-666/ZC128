#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

enum Opcode{
    NOP=0,
    MOV=1,
    ADD=2,
    SUB=3,
    AND=4,
    OR=5,
    XOR=6,
    NOT=7,
    JMP=8,
    CMP=9,
    BEQ=10,
    BNE=11,
    LOAD = 12,
    STORE = 13,
    SHL = 14,
    SHR = 15,
    NEG = 16,
    JZ = 17,
    MUL = 18,
    DIV = 19,
    MOD = 20,
    NOP = 21,
    HLT=255,
};


struct Instruction {
    Opcode op; // 操作码
    int dst;
    int src1; // 源操作数1
    int src2; // 源操作数2
    int imm; // 立即数
};

Instruction decode(const bool inst[128]);

void encode(const Instruction& ins, bool out[128]);

#endif // INSTRUCTIONSET_H