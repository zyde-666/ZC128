#include "../include/core.h"

Core::Core(int cid, Mem& sharedM, Cache& sharedC)
    : core_id(cid), sharedMem(sharedM), sharedCache(sharedC),
      threads{Thread(cid * 2), Thread(cid * 2 + 1)} {}

void Core::loadThreadProgram(int tid, const bool program[][128], int size) {
    if (tid == 0 || tid == 1) {
        threads[tid].loadProgram(program, size);
    }
}

void Core::tick() {
    for (int i = 0; i < 2; ++i) {
        if (!threads[i].isHalted()) {
            threads[i].tick(sharedMem, sharedCache);
        }
    }
}

bool Core::allHalted() const {
    return threads[0].isHalted() && threads[1].isHalted();
}

void Core::dumpThread(int localTid) const {
    if (localTid >= 0 && localTid < 2)
        threads[localTid].dump();
}

bool Core::allThreadsHalted() {
    return threads[0].isHalted() && threads[1].isHalted();
}


