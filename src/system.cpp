#include "../include/system.h"

System::System() {
    for (int i = 0; i < NUM_CORES; ++i) {
        cores[i] = new Core(i, sharedMem, sharedCache);
    }
}

System::~System() {
    for (int i = 0; i < NUM_CORES; ++i) {
        delete cores[i];
    }
}

void System::loadProgramToThread(int globalTid, const bool program[][128], int size) {
    int coreId = globalTid / 2;
    int localTid = globalTid % 2;
    if (coreId >= 0 && coreId < NUM_CORES) {
        cores[coreId]->loadThreadProgram(localTid, program, size);
    }
}

void System::run() {
    std::cout << "System started.\n";
    bool allHalted = false;
    int tickCount = 0;

    while (!allHalted) {
        for (int i = 0; i < NUM_CORES; ++i) {
            cores[i]->tick();
        }
        if (tickCount % 1000 == 0) {
            std::cout << "Thread states:\n";
            for (int i = 0; i < NUM_CORES; ++i) {
                for (int j = 0; j < 2; ++j) {
                    std::cout << "- Core " << i << ", Thread " << (i*2 + j) << ": ";
                    cores[i]->dumpThread(j);
                }
            }
        }

        // 检查是否所有线程都 halt 了
        allHalted = true;
        for (int i = 0; i < NUM_CORES; ++i) {
            if (!cores[i]->allThreadsHalted()) {
                allHalted = false;
                break;
            }
        }

        tickCount++;
    }
}
