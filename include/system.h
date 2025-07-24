#ifndef SYSTEM_H
#define SYSTEM_H

#include "core.h"
#include "Memory.h"
#include "Cache.h"
#include <iostream>


class System {
private:
    static const int NUM_CORES = 4;
    Core* cores[NUM_CORES];
    Mem sharedMem;
    Cache sharedCache;

public:
    System();
    ~System();

    void loadProgramToThread(int globalTid, const bool program[][128], int size);
    void run(); // 启动系统，直到所有线程结束
};

#endif
