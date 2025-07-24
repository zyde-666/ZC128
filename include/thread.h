#ifndef THREAD_H
#define THREAD_H

#include "RF.h"
#include "pc.h"
#include "Memory.h"
#include "Cache.h"
#include "InstructionSet.h"
#include "executor.h"

class Thread {
private:
    int id;
    RF rf;
    PC pc;
    Mem localMem;      // 16x128
    Cache localCache;  // 4-line
    bool cmp_flag;
    bool halted;

public:
    Thread(int tid);

    void loadProgram(const bool program[][128], int size);
    void tick(Mem& sharedMem, Cache& sharedCache);
    bool isHalted() const;
    int getID() const;
    void dump() const;
};

#endif
