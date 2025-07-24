//ALU_LG.cpp
#include "../include/ALU_LG.h"

namespace LG {
    bool SB_LC::AND(bool a, bool b) {
        return a && b;
    }

    bool SB_LC::OR(bool a, bool b) {
        return a || b;
    }

    bool SB_LC::NOT(bool a) {
        return !a;
    }

    bool SB_LC::NAND(bool a, bool b) {
        return !(a && b);
    }

    bool SB_LC::NOR(bool a, bool b) {
        return !(a || b);
    }

    bool SB_LC::XOR(bool a, bool b) {
        return a ^ b;
    }

    bool SB_LC::XNOR(bool a, bool b) {
        return !(a ^ b);
    }
    
    void MB_LG::AND(const bool a[128], const bool b[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) result[i] = a[i] && b[i];
    }

    void MB_LG::OR(const bool a[128], const bool b[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) result[i] = a[i] || b[i];
    }

    void MB_LG::NOT(const bool a[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) result[i] = !a[i];
    }

    void MB_LG::XOR(const bool a[128], const bool b[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) result[i] = a[i] ^ b[i];
    }

    void MB_LG::NAND(const bool a[128], const bool b[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) result[i] = !(a[i] && b[i]);
    }

    void MB_LG::NOR(const bool a[128], const bool b[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) result[i] = !(a[i] || b[i]);
    }

    void MB_LG::XNOR(const bool a[128], const bool b[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) result[i] = !(a[i] ^ b[i]);
    }



} // namespace LG

namespace ALU {

    void ALU128::add128(const bool a[128], const bool b[128], bool result[128]) {
        bool carry = false;
        for (int i = 0; i < 128; ++i) {
            bool sum = a[i] ^ b[i] ^ carry;
            bool new_carry = (a[i] && b[i]) || (carry && (a[i] ^ b[i]));
            result[i] = sum;
            carry = new_carry;
        }
    }
    

    void ALU128::sub128(const bool a[128], const bool b[128], bool result[128]) {
        bool borrow = false;
        for (int i = 0; i < 128; ++i) {
            bool diff = a[i] ^ b[i] ^ borrow;
            bool new_borrow = (!a[i] && b[i]) || (borrow && (a[i] ^ b[i]));
            result[i] = diff;
            borrow = new_borrow;
        }
    }

    void ALU128::mul128(const bool a[128], const bool b[128], bool result[128]) {
        for (int i = 0; i < 128; ++i) {
            result[i] = false; // Initialize result to zero
        }
        for (int i = 0; i < 128; ++i) {
            if (b[i]) {
                bool temp[128] = {false};
                for (int j = 0; j < 128 - i; ++j) {
                    temp[j + i] = a[j];
                }
                bool carry = false;
                for (int j = 0; j < 128; ++j) {
                    bool sum = result[j] ^ temp[j] ^ carry;
                    carry = (result[j] && temp[j]) || (carry && (result[j] ^ temp[j]));
                    result[j] = sum;
                }
            }
        }
    }

    void ALU128::div128(const bool a[128], const bool b[128], bool result[128], bool remainder[128]) {
        for (int i = 0; i < 128; ++i) {
            result[i] = false; // Initialize result to zero
            remainder[i] = a[i]; // Start with the dividend
        }

        for (int i = 127; i >= 0; --i) {
            bool temp[128] = {false};
            for (int j = 0; j < 128 - i; ++j) {
                temp[j + i] = b[j];
            }
            if (ALU::ALU128::ge128(remainder, temp)) {
                sub128(remainder, temp, remainder);
                result[i] = true;
            }
        }
    }

    void ALU128::mod128(const bool a[128], const bool b[128], bool result[128]) {
        bool remainder[128] = {false};
        for (int i = 0; i < 128; ++i) {
            remainder[i] = a[i]; // Start with the dividend
        }

        for (int i = 127; i >= 0; --i) {
            bool temp[128] = {false};
            for (int j = 0; j < 128 - i; ++j) {
                temp[j + i] = b[j];
            }
            if (ALU::ALU128::ge128(remainder, temp)) {
                sub128(remainder, temp, remainder);
            }
        }
        for (int i = 0; i < 128; ++i) {
            result[i] = remainder[i];
        }
    }

    void ALU128::neg128(const bool a[128], bool result[128]) {
        bool carry = true; // Start with carry for two's complement
        for (int i = 0; i < 128; ++i) {
            result[i] = !a[i] ^ carry; // Invert bits and add carry
            carry = !a[i] && carry || a[i] && !carry; // Calculate new carry
        }
    }

    void ALU128::inc128(const bool a[128], bool result[128]) {
        bool carry = true; // Start with carry for increment
        for (int i = 0; i < 128; ++i) {
            result[i] = a[i] ^ carry; // Add carry to the current bit
            carry = a[i] && carry; // Calculate new carry
        }
    }

    void ALU128::dec128(const bool a[128], bool result[128]) {
        bool borrow = true; // Start with borrow for decrement
        for (int i = 0; i < 128; ++i) {
            result[i] = a[i] ^ borrow; // Subtract borrow from the current bit
            borrow = !a[i] && borrow; // Calculate new borrow
        }
    }

    void ALU128::shift_left(bool a[128]) {
        for (int i = 127; i > 0; --i) {
            a[i] = a[i - 1];
        }
        a[0] = false; // Clear the least significant bit
    }

    void ALU128::shift_right(bool a[128]) {
        for (int i = 0; i < 127; ++i) {
            a[i] = a[i + 1];
        }
        a[127] = false; // Clear the most significant bit
    }

    void ALU128::rol128(bool a[128]) {
        bool temp = a[127];
        for (int i = 127; i > 0; --i) {
            a[i] = a[i - 1];
        }
        a[0] = temp;
    }

    void ALU128::ror128(bool a[128]) {
        bool temp = a[0];
        for (int i = 0; i < 127; ++i) {
            a[i] = a[i + 1];
        }
        a[127] = temp;
    }

    bool ALU128::ge128(const bool a[128], const bool b[128]) {
        for (int i = 127; i >= 0; --i) {
            if (a[i] && !b[i]) {
                 // a > b
                return true;
            }
            if (!a[i] && b[i]) {
                 // a < b
                return false;
            }
        }
         // a == b
        return true;
    }

    bool ALU128::eq128(const bool a[128], const bool b[128]) {
        for (int i = 0; i < 128; ++i) {
            if (a[i] != b[i]) {
                return false; // Found a mismatch
            }
        }
        return true; // All bits are equal
    }

    bool ALU128::lt128(const bool a[128], const bool b[128]) {
        for (int i = 127; i >= 0; --i) {
            if (a[i] && !b[i]) {
                return false; // a > b
            }
            if (!a[i] && b[i]) {
                return true; // a < b
            }
        }
        return false; // a == b
    }

    bool ALU128::le128(const bool a[128], const bool b[128]) {
        return lt128(a, b) || eq128(a, b);
    }

    bool ALU128::gt128(const bool a[128], const bool b[128]) {
        return !le128(a, b);
    }

    bool ALU128::ne128(const bool a[128], const bool b[128]) {
        return !eq128(a, b);
    }


}