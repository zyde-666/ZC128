#include "../include/thread.h"
#include "../include/system.h"

Thread::Thread(int tid) : id(tid), halted(false), cmp_flag(false) {}

void Thread::loadProgram(const bool program[][128], int size) {
    std::cout << "Loading program into thread " << id << " of size " << size << "\n";
    for (int i = 0; i < size; ++i) {
        localMem.write(i, program[i]);

        std::cout << "Instruction[" << i << "] opcode bits: ";
        for (int b = 0; b < 8; ++b)
            std::cout << program[i][b];
        std::cout << "\n";

        if (i == 42) {
            std::cout << "prog[42] opcode bits: ";
            for (int b = 0; b < 8; ++b)
                std::cout << program[i][b];
            std::cout << "\n";
        }
        
    }

}



void Thread::tick(Mem& sharedMem, Cache& sharedCache) {
    if (halted) return;

    int pc_val = pc.get();
    if (pc_val >= 128) {
        std::cerr << "⚠️ Thread " << id << " PC=" << pc_val << " out of bounds! Halting.\n";
        halted = true;
        return;
    }

    bool inst_bits[128];
    localMem.read(pc_val, inst_bits);
    Instruction inst = decode(inst_bits);

    std::cout << "Thread " << id << " executing PC=" << pc_val << ", opcode=" << inst.op << "\n";
    execute(inst, rf, pc, cmp_flag, sharedMem, halted);
}





bool Thread::isHalted() const {
    return halted;
}

int Thread::getID() const {
    return id;
}

void Thread::dump() const {
    std::cout << "Thread " << id << " PC=" << pc.get() << (halted ? " (halted)" : "") << "\n";
}
