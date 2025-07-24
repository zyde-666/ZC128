#ifndef ALU_LG_H
#define ALU_LG_H
//LG=逻辑门
namespace LG{//逻辑门
class SB_LC {
    public:
        static bool AND(bool a, bool b);
        static bool OR(bool a, bool b);
        static bool NOT(bool a);
        static bool NAND(bool a, bool b);
        static bool NOR(bool a, bool b);
        static bool XOR(bool a, bool b);
        static bool XNOR(bool a, bool b);
    };
    
    // 固定 128 位逻辑操作
    class MB_LG {
    public:
        static void AND(const bool a[128], const bool b[128], bool result[128]);
        static void OR(const bool a[128], const bool b[128], bool result[128]);
        static void NOT(const bool a[128], bool result[128]);
        static void XOR(const bool a[128], const bool b[128], bool result[128]);
        static void NAND(const bool a[128], const bool b[128], bool result[128]);
        static void NOR(const bool a[128], const bool b[128], bool result[128]);
        static void XNOR(const bool a[128], const bool b[128], bool result[128]);
   };
}

namespace ALU{
    class ALU128{
        public:
        static void add128(const bool a[128], const bool b[128], bool result[128]);
        static void sub128(const bool a[128], const bool b[128], bool result[128]);
        static void mul128(const bool a[128], const bool b[128], bool result[128]);
        static void div128(const bool a[128], const bool b[128], bool result[128], bool remainder[128]);
        static void mod128(const bool a[128], const bool b[128], bool result[128]);
        static void neg128(const bool a[128], bool result[128]);
        static void inc128(const bool a[128], bool result[128]);
        static void dec128(const bool a[128], bool result[128]);

        static void shift_left(bool a[128]);
        static void shift_right(bool a[128]);
        static void rol128(bool a[128]);
        static void ror128(bool a[128]);

        static bool ge128(const bool a[128], const bool b[128]);
        static bool eq128(const bool a[128], const bool b[128]);
        static bool lt128(const bool a[128], const bool b[128]);
        static bool le128(const bool a[128], const bool b[128]);
        static bool gt128(const bool a[128], const bool b[128]);
        static bool ne128(const bool a[128], const bool b[128]);
    };

}
#endif // ALU_LG_H