#ifndef CORE_H
#define CORE_H

#include "thread.h"
#include "Memory.h"
#include "Cache.h"

class Core {
private:
    int core_id;
    Thread threads[2];         // 每个Core两个线程
    Mem& sharedMem;
    Cache& sharedCache;

public:
    Core(int cid, Mem& sharedM, Cache& sharedC);

    void loadThreadProgram(int tid, const bool program[][128], int size);
    void tick();  // 让两个线程各跑一步
    bool allHalted() const;
    void dumpThread(int localTid) const;
    bool allThreadsHalted();
};

#endif
