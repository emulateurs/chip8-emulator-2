//
// Created by leroideskiwis on 10/01/25.
//

#include "Chip8.h"

#include <format>
#include <stdexcept>

void Chip8::load(const std::string& fileName)
{
}

void Chip8::tick()
{
    const byte left_byte = memory[memory.program_counter];
    const byte right_byte = memory[memory.program_counter + 1];

    memory.program_counter += 2;
    process(left_byte, right_byte);
}

void Chip8::process(byte left_opcode, byte right_opcode)
{
    const int opcode = (left_opcode << 8) | right_opcode;

    const int nnn = opcode & 0x0FFF;
    int x = left_opcode & 0x0F;
    int y = right_opcode >> 4;

    switch (left_opcode & 0xF0)
    {
        break;
    default:
        throw std::invalid_argument(std::format("Wrong opcode detected : {}", opcode));
    }
}
