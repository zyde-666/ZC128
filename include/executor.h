#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "RF.h"
#include "pc.h"
#include "InstructionSet.h"
#include "Memory.h"
#include "Cache.h"
#include "ALU_LG.h"

void execute(const Instruction& inst, RF& rf, PC& pc, bool cmp_flag, Mem& memory, bool& halted);

#endif
