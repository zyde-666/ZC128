# ZC128 项目

## 项目简介
ZC128 是一个模拟简单 CPU 的项目，支持 128 位宽度的寄存器、内存和指令集。该项目旨在模拟多核多线程的 CPU 运行环境，提供基本的指令执行、内存管理和缓存功能。

## 功能特点
- **多核多线程支持**：每个核心包含两个线程，系统支持多个核心并行运行。
- **128 位架构**：寄存器、内存和指令均为 128 位宽度。
- **指令集支持**：实现了基本的算术、逻辑、跳转和内存操作指令。
- **缓存机制**：支持简单的缓存读写和刷新操作。
- **模块化设计**：代码分为多个模块，便于扩展和维护。

## 项目结构
```
ZC128/
├── include/          # 头文件目录
│   ├── ALU_LG.h      # 算术逻辑单元和逻辑门实现
│   ├── Cache.h       # 缓存实现
│   ├── core.h        # 核心模块
│   ├── executor.h    # 指令执行器
│   ├── InstructionSet.h # 指令集定义与编码/解码
│   ├── Memory.h      # 内存模块
│   ├── pc.h          # 程序计数器
│   ├── RF.h          # 寄存器文件
│   ├── system.h      # 系统模块
│   └── thread.h      # 线程模块
├── src/              # 源代码目录
│   ├── ALU_LG.cpp    # 算术逻辑单元实现
│   ├── Cache.cpp     # 缓存实现
│   ├── core.cpp      # 核心模块实现
│   ├── executor.cpp  # 指令执行器实现
│   ├── InstructionSet.cpp # 指令集实现
│   ├── Memory.cpp    # 内存模块实现
│   ├── pc.cpp        # 程序计数器实现
│   ├── RF.cpp        # 寄存器文件实现
│   ├── system.cpp    # 系统模块实现
│   └── thread.cpp    # 线程模块实现
├── test.cpp          # 测试代码
├── CMakeLists.txt    # CMake 构建配置文件
└── README.md         # 项目说明文件
```

## 编译与运行
### 环境要求
- C++17 或更高版本
- CMake 3.10 或更高版本

### 编译步骤
1. 在项目根目录下创建 `build` 文件夹：
   ```bash
   mkdir build && cd build
   ```
2. 使用 CMake 生成构建文件：
   ```bash
   cmake ..
   ```
3. 编译项目：
   ```bash
   make
   ```

### 运行
编译完成后，生成的可执行文件为 `SimpleCPU`，运行命令如下：
```bash
./SimpleCPU
```
## 指令格式说明

ZC128 的每条指令长度为 128 位，编码格式如下：

| 位范围     | 字段   | 描述               |
|------------|--------|--------------------|
| 0 - 7      | op     | 操作码（Opcode）   |
| 8 - 13     | dst    | 目标寄存器编号     |
| 14 - 19    | src1   | 源寄存器1编号      |
| 20 - 25    | src2   | 源寄存器2编号      |
| 26 - 127   | imm    | 立即数（int 类型） |

### 支持的指令集（Opcode）

| 指令 | 含义           |
|------|----------------|
| NOP  | 空操作         |
| MOV  | 立即数写入寄存器 |
| ADD  | 加法           |
| SUB  | 减法           |
| AND  | 按位与         |
| OR   | 按位或         |
| XOR  | 按位异或       |
| NOT  | 按位取反       |
| SHL  | 左移           |
| SHR  | 右移           |
| NEG  | 取负（补码）   |
| MUL  | 乘法           |
| DIV  | 除法           |
| MOD  | 取模           |
| CMP  | 比较寄存器是否相等（设置 cmp_flag）|
| BEQ  | 若 cmp_flag 为真则跳转（相等跳转）|
| BNE  | 若 cmp_flag 为假则跳转（不等跳转）|
| JMP  | 无条件跳转到地址 |
| LOAD | 从内存读取     |
| STORE| 写入内存       |
| HLT  | 停止线程执行   |


## 使用说明
1. **加载程序**：通过 `System::loadProgramToThread` 方法将程序加载到指定线程。
2. **运行系统**：调用 `System::run` 方法启动系统，直到所有线程结束。
3. **调试信息**：运行过程中会输出每个线程的状态和执行的指令。
4. **自定义调试**：你可以在 `test.cpp` 文件中添加自己的 `main` 函数，自定义测试或调试指令执行流程。


## 扩展与维护
- **新增指令**：在 `InstructionSet.h` 中定义新的操作码，并在 `executor.cpp` 中实现对应的执行逻辑。
- **优化性能**：可以改进缓存策略或增加流水线模拟以提升性能。
- **增加测试**：在 `test.cpp` 中添加更多测试用例，验证系统功能。

## 贡献
欢迎对本项目提出改进建议或提交代码贡献！如有问题，请联系项目维护者。

## 许可证
本项目遵循 MIT 许可证，详情请参阅 LICENSE 文件。



感谢阅读！欢迎 Star⭐、Fork🍴或提 Issue 🎯


---

# ZC128 Project

## Project Overview
ZC128 is a project that simulates a simple CPU with 128-bit wide registers, memory, and instruction set. The project aims to emulate a multi-core, multi-threaded CPU environment, providing basic instruction execution, memory management, and caching functionality.

## Features
- **Multi-core and Multi-threading Support**: Each core contains two threads, and the system supports multiple cores running in parallel.
- **128-bit Architecture**: Registers, memory, and instructions are all 128 bits wide.
- **Instruction Set Support**: Implements basic arithmetic, logic, jump, and memory operation instructions.
- **Caching Mechanism**: Supports simple cache read, write, and flush operations.
- **Modular Design**: The code is divided into multiple modules for easy extension and maintenance.

## Project Structure
```
ZC128/
├── include/          # Header files
│   ├── ALU_LG.h      # Arithmetic Logic Unit and Logic Gates
│   ├── Cache.h       # Cache implementation
│   ├── core.h        # Core module
│   ├── executor.h    # Instruction executor
│   ├── InstructionSet.h # Instruction set definition and encoding/decoding
│   ├── Memory.h      # Memory module
│   ├── pc.h          # Program counter
│   ├── RF.h          # Register file
│   ├── system.h      # System module
│   └── thread.h      # Thread module
├── src/              # Source code
│   ├── ALU_LG.cpp    # Arithmetic Logic Unit implementation
│   ├── Cache.cpp     # Cache implementation
│   ├── core.cpp      # Core module implementation
│   ├── executor.cpp  # Instruction executor implementation
│   ├── InstructionSet.cpp # Instruction set implementation
│   ├── Memory.cpp    # Memory module implementation
│   ├── pc.cpp        # Program counter implementation
│   ├── RF.cpp        # Register file implementation
│   ├── system.cpp    # System module implementation
│   └── thread.cpp    # Thread module implementation
├── test.cpp          # Test code
├── CMakeLists.txt    # CMake build configuration
└── README.md         # Project documentation
```

## Build and Run
### Requirements
- C++17 or higher
- CMake 3.10 or higher

### Build Steps
1. Create a `build` folder in the project root directory:
   ```bash
   mkdir build && cd build
   ```
2. Generate build files using CMake:
   ```bash
   cmake ..
   ```
3. Compile the project:
   ```bash
   make
   ```

### Run
After compilation, the executable file `SimpleCPU` will be generated. Run it with the following command:
```bash
./SimpleCPU
```

## Instruction Format

Each instruction in ZC128 is 128 bits wide, encoded as follows:

| Bit Range   | Field | Description               |
|-------------|-------|---------------------------|
| 0 - 7       | op    | Opcode                    |
| 8 - 13      | dst   | Destination register index|
| 14 - 19     | src1  | Source register 1 index   |
| 20 - 25     | src2  | Source register 2 index   |
| 26 - 127    | imm   | Immediate value (int)     |

### Supported Instructions (Opcode)

| Mnemonic | Description                     |
|----------|---------------------------------|
| NOP      | No operation                    |
| MOV      | Move immediate to register      |
| ADD      | Addition                        |
| SUB      | Subtraction                     |
| AND      | Bitwise AND                     |
| OR       | Bitwise OR                      |
| XOR      | Bitwise XOR                     |
| NOT      | Bitwise NOT                     |
| SHL      | Logical left shift              |
| SHR      | Logical right shift             |
| NEG      | Two's complement (negation)     |
| MUL      | Multiplication                  |
| DIV      | Division                        |
| MOD      | Modulus                         |
| CMP      | Compare registers (set cmp_flag)|
| BEQ      | Branch if equal                 |
| BNE      | Branch if not equal             |
| JMP      | Unconditional jump              |
| LOAD     | Load from memory                |
| STORE    | Store to memory                 |
| HLT      | Halt thread                     |


## Usage
1. **Load Program**: Use the `System::loadProgramToThread` method to load a program into a specific thread.
2. **Run System**: Call the `System::run` method to start the system until all threads finish execution.
3. **Debug Information**: During execution, the state of each thread and the instructions being executed will be output.
4. **Custom Debugging**: You can add your own `main` function in `test.cpp` to run custom tests or debug the instruction execution flow.


## Extensions and Maintenance
- **Add New Instructions**: Define new opcodes in `InstructionSet.h` and implement their execution logic in `executor.cpp`.
- **Optimize Performance**: Improve caching strategies or add pipeline simulation to enhance performance.
- **Add Tests**: Add more test cases in `test.cpp` to verify system functionality.

## Contribution
Contributions and suggestions for improvement are welcome! If you encounter any issues, please contact the project maintainers.

## License
This project is licensed under the MIT License. See the LICENSE file for details.



Thanks for reading! Feel free to star ⭐ the project or contribute 🤝.

