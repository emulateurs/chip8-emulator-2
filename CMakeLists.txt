cmake_minimum_required(VERSION 3.30)
project(chip8_emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(chip8_emulator main.cpp
        Chip8.cpp
        Chip8.h)
