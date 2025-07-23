#include <iostream>
#include "include/RF.h"
#include "include/ALU_LG.h"
#include "include/pc.h"
#include "include/InstructionSet.h"

// 执行指令
void execute(const Instruction& inst, RF& rf, PC& pc, bool& cmp_flag, bool& halted) {
    bool a[128] = {false}, b[128] = {false}, result[128] = {false};

    switch (inst.op) {
        case MOV:
            for (int i = 0; i < 128; ++i)
                a[i] = (inst.imm >> i) & 1;
            rf.write(inst.dst, a);
            break;

        case ADD:
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            ALU::ALU128::add128(a, b, result);
            rf.write(inst.dst, result);
            break;

        case SUB:
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            ALU::ALU128::sub128(a, b, result);
            rf.write(inst.dst, result);
            break;

        case CMP:
            cmp_flag = rf.eq(inst.src1, inst.src2);
            break;

        case BEQ:
            if (cmp_flag) pc.add(inst.imm);
            break;

        case JMP:
            rf.read(inst.src1, a);
            {
                int addr = 0;
                for (int i = 0; i < 32; ++i)
                    if (a[i]) addr |= (1 << i);
                pc.set(addr);
            }
            break;

        case HLT:
            std::cout << "Program halted.\n";
            halted = true;
            break;

        default:
            break;
    }
}

void printReg(RF& rf, int reg) {
    bool out[128];
    rf.read(reg, out);
    std::cout << "R" << reg << " = ";
    for (int i = 127; i >= 0; --i) {
        std::cout << out[i];
    }
    std::cout << "\n";
}

int main() {
    bool halted = false;
    RF rf;
    PC pc;
    bool cmp_flag = false;

    // 用数组表示程序存储器
    const int PROG_SIZE = 10;
    bool program[PROG_SIZE][128];

    // 写入程序：MOV R0, #5
    encode({MOV, 0, -1, -1, 5}, program[0]);
    // MOV R1, #10
    encode({MOV, 1, -1, -1, 10}, program[1]);
    // ADD R2 = R0 + R1
    encode({ADD, 2, 0, 1}, program[2]);
    // CMP R0, R1
    encode({CMP, -1, 0, 1}, program[3]);
    // BEQ +2
    encode({BEQ, -1, -1, -1, 2}, program[4]);
    // MOV R3, #999
    encode({MOV, 3, -1, -1, 999}, program[5]);
    // HLT
    encode({HLT}, program[6]);

    std::cout << "Running program...\n";

    // 主循环
    while (!halted) {
        int addr = pc.get();
        if (addr < 0 || addr >= PROG_SIZE) {
            std::cerr << "PC out of range!\n";
            break;
        }
    
        Instruction inst = decode(program[addr]);
        execute(inst, rf, pc, cmp_flag, halted);
        pc.increment();
    }
    

    // 输出寄存器状态
    std::cout << "\n--- Register Dump ---\n";
    for (int i = 0; i < 4; ++i) {
        printReg(rf, i);
    }
    

    return 0;
}
