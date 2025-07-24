#include "../include/executor.h"
#include "../include/system.h"
//void execute(const Instruction& inst, RegisterFile& rf, PC& pc, bool cmp_flag, Mem& memory, bool& halted)

void execute(const Instruction& inst, RF& rf, PC& pc, bool cmp_flag, Mem& memory, bool& halted) {
    bool a[128] = {false}, b[128] = {false}, result[128] = {false};

    std::cout << "[Thread] executing opcode = " << inst.op << "\n";

    switch (inst.op) {
        case MOV:
            for (int i = 0; i < 128; ++i)
                a[i] = (inst.imm >> i) & 1;
            rf.write(inst.dst, a);
            pc.increment(); // ✅ 正常流程
            break;

        case ADD:
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            ALU::ALU128::add128(a, b, result);
            rf.write(inst.dst, result);
            pc.increment();
            break;

        case SUB:
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            ALU::ALU128::sub128(a, b, result);
            rf.write(inst.dst, result);
            pc.increment();
            break;

        case CMP:
            cmp_flag = rf.eq(inst.src1, inst.src2);
            pc.increment();
            break;

        case BEQ:
            if (cmp_flag) pc.add(inst.imm);
            else pc.increment();
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
            halted = true;
            break;

        case LOAD:
            {
                bool temp[128];
                memory.read(inst.imm, temp);
                rf.write(inst.dst, temp);
                pc.increment();
            }
            break;

        case STORE:
            {
                bool temp[128];
                rf.read(inst.src1, temp);
                memory.write(inst.imm, temp);
                pc.increment();
            }
            break;

        case SHL:
            {
                bool temp[128];
                rf.read(inst.src1, temp);
                ALU::ALU128::shift_left(temp);
                rf.write(inst.dst, temp);
                pc.increment();
            }
            break;

        case SHR:
            {
                bool temp[128];
                rf.read(inst.src1, temp);
                ALU::ALU128::shift_right(temp);
                rf.write(inst.dst, temp);
                pc.increment();
            }
            break;

        case NEG:
            {
                bool temp[128];
                rf.read(inst.src1, temp);
                ALU::ALU128::neg128(temp, temp);
                rf.write(inst.dst, temp);
                pc.increment();
            }
            break;

        case AND:
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            LG::MB_LG::AND(a, b, result);
            rf.write(inst.dst, result);
            pc.increment();
            break;

        case OR:
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            LG::MB_LG::OR(a, b, result);
            rf.write(inst.dst, result);
            pc.increment();
            break;

        case XOR:
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            LG::MB_LG::XOR(a, b, result);
            rf.write(inst.dst, result);
            pc.increment();
            break;

        case NOT:
            rf.read(inst.src1, a);
            LG::MB_LG::NOT(a, result);
            rf.write(inst.dst, result);
            pc.increment();
            break;

        
        case MUL:
        {
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            ALU::ALU128::mul128(a, b, result);
            rf.write(inst.dst, result);
            break;
        }
        
        case DIV:
        {
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            bool remainder[128] = {false};  // ✅ 增加这一行
            ALU::ALU128::div128(a, b, result, remainder);  // ✅ 参数齐全
            rf.write(inst.dst, result);
            break;
        }
        
        
        case MOD:
        {
            rf.read(inst.src1, a);
            rf.read(inst.src2, b);
            ALU::ALU128::mod128(a, b, result);  // 会实现在下一步
            rf.write(inst.dst, result);
            break;
        }
        
        case NOP:
            // ✅ 什么都不做
            break;


        default:
            std::cerr << "❌ Unknown opcode: " << inst.op << "\n";
            halted = true;  // 出错也 halt
            break;
    }
}
