cmake_minimum_required(VERSION 3.10)
project(SimpleCPU LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/RF.cpp
    ${CMAKE_SOURCE_DIR}/src/pc.cpp
    ${CMAKE_SOURCE_DIR}/src/ALU_LG.cpp
    ${CMAKE_SOURCE_DIR}/src/InstructionSet.cpp
    ${CMAKE_SOURCE_DIR}/test.cpp
)
#生成可执行文件
add_executable(SimpleCPU ${SOURCES})
