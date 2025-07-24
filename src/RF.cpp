//RF.cpp
#include "../include/RF.h"

RF::RF() {
    for (int i = 0; i < 64; ++i) {
        for (int j = 0; j < 128; ++j) {
            registers[i][j] = false;
        }
    }
}

void RF::write(int index, const bool data[128]) {
    if (index < 0 || index >= 64) return;  // 防止越界写入
    for (int i = 0; i < 128; ++i) {
        registers[index][i] = data[i];
    }
}

void RF::read(int index, bool out[128]) const {
    if (index < 0 || index >= 64) return;  // 防止越界读取
    for (int i = 0; i < 128; ++i) {
        out[i] = registers[index][i];
    }
}

void RF::clean() {
    for (int i = 0; i < 64; ++i) {
        for (int j = 0; j < 128; ++j) {
            registers[i][j] = false;
        }
    }
}

void RF::copy(int from, int to) {
    if (from < 0 || from >= 64 || to < 0 || to >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[to][i] = registers[from][i];
    }
}

void RF::readPair(int r1, int r2, int r3, int r4, bool out1[128], bool out2[128], bool out3[128], bool out4[128]) {
    read(r1, out1);
    read(r2, out2);
    read(r3, out3);
    read(r4, out4);
}

void RF::setBit(int reg, int BitIndex, bool val) {
    if (reg < 0 || reg >= 64 || BitIndex < 0 || BitIndex >= 128) return;  // 防止越界
    registers[reg][BitIndex] = val;
}

bool RF::getBit(int reg, int BitIndex) {
    if (reg < 0 || reg >= 64 || BitIndex < 0 || BitIndex >= 128) return false;  // 防止越界
    return registers[reg][BitIndex];
}

bool RF::eq(int reg1, int reg2) const {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64) return false;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        if (registers[reg1][i] != registers[reg2][i]) {
            return false;
        }
    }
    return true;
}

bool RF::zf(int reg) const {
    if (reg < 0 || reg >= 64) return false;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        if (registers[reg][i]) {
            return false;  // 如果有任意一位为1，则不为零
        }
    }
    return true;  // 全部位为0
}

void RF::getSlice(int reg, int start, int end, bool out[128]) const {
    if (reg < 0 || reg >= 64 || start < 0 || end < 0 || start >= end || end > 128) return;  // 防止越界
    for (int i = start; i < end; ++i) {
        out[i - start] = registers[reg][i];
    }
}

void RF::setSlice(int reg, int start, int end, const bool data[128]) {
    if (reg < 0 || reg >= 64 || start < 0 || end < 0 || start >= end || end > 128) return;  // 防止越界
    for (int i = start; i < end; ++i) {
        registers[reg][i] = data[i - start];
    }
}

void RF::BitwiseAnd(int reg1, int reg2, int outReg) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = registers[reg1][i] && registers[reg2][i];
    }
}

void RF::BitwiseOr(int reg1, int reg2, int outReg) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = registers[reg1][i] || registers[reg2][i];
    }
}

void RF::BitwiseXor(int reg1, int reg2, int outReg) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = registers[reg1][i] ^ registers[reg2][i];
    }
}

void RF::BitwiseNot(int reg, int outReg) {
    if (reg < 0 || reg >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = !registers[reg][i];
    }
}

void RF::BitwiseNand(int reg1, int reg2, int outReg) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = !(registers[reg1][i] && registers[reg2][i]);
    }
}

void RF::BitwiseNor(int reg1, int reg2, int outReg) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = !(registers[reg1][i] || registers[reg2][i]);
    }
}

void RF::BitwiseXnor(int reg1, int reg2, int outReg) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = !(registers[reg1][i] ^ registers[reg2][i]);
    }
}

void RF::Bit_SL(int reg, int outReg) {
    if (reg < 0 || reg >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 127; ++i) {
        registers[outReg][i] = registers[reg][i + 1];
    }
    registers[outReg][127] = false; // 最后一个位清零
}

void RF::Bit_SR(int reg, int outReg) {
    if (reg < 0 || reg >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 127; i > 0; --i) {
        registers[outReg][i] = registers[reg][i - 1];
    }
    registers[outReg][0] = false; // 第一个位清零
}

void RF::Bit_RF(int reg, int outReg) {
    if (reg < 0 || reg >= 64 || outReg < 0 || outReg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = registers[reg][(i + 1) % 128];
    }
}

void RF::set_ALL(int reg) {
    if (reg < 0 || reg >= 64) return;  // 防止越界
    for (int i = 0; i < 128; ++i) {
        registers[reg][i] = true; // 设置所有位为1
    }
}

bool RF::cmp(int reg1, int reg2, int outReg) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64 || outReg < 0 || outReg >= 64) return false;  // 防止越界
    bool result = eq(reg1, reg2);
    for (int i = 0; i < 128; ++i) {
        registers[outReg][i] = result;
    }
    return result;
}

void RF::Bit_swap(int reg1, int reg2) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64) return;  // 防止越界
    bool temp[128];
    read(reg1, temp);
    write(reg1, registers[reg2]);
    write(reg2, temp);
}

int RF::Bit_sub(int reg1, int reg2) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64) return 0;  // 防止越界
    int result = 0;
    for (int i = 0; i < 128; ++i) {
        if (registers[reg1][i] && !registers[reg2][i]) {
            result |= (1 << i); // 设置对应位
        }
    }
    return result;
}

int RF::maskAnd(int reg1, int reg2) {
    if (reg1 < 0 || reg1 >= 64 || reg2 < 0 || reg2 >= 64) return 0;  // 防止越界
    int result = 0;
    for (int i = 0; i < 128; ++i) {
        if (registers[reg1][i] && registers[reg2][i]) {
            result |= (1 << i); // 设置对应位
        }
    }
    return result;
}





