# 最低 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(mbedtls_hashtest C)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


# 包含 mbedTLS 头文件目录
include_directories(crypto)

aux_source_directory(crypto SRC_LIST)

# 添加可执行文件（假设主源码文件为 main.c）
add_executable(hashtest_file main.c ${SRC_LIST})

