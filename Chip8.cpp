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

    const int before_pc = memory.program_counter;
    process(left_byte, right_byte);
    if (before_pc == memory.program_counter) memory.program_counter+=2;
}

void Chip8::process(byte left_opcode, byte right_opcode)
{
    const int opcode = (left_opcode << 8) | right_opcode;

    const int nnn = opcode & 0x0FFF;
    int x = left_opcode & 0x0F;
    int y = right_opcode >> 4;

    switch (left_opcode & 0xF0)
    {
    case 0x00:
        switch (right_opcode)
        {
        case 0xE0: //CLS (clear)
            break;
        case 0xEE: //RET
            memory.ret();
            break;
        default:
            break;
        }
        break;
    case 0x10: //JP addr
        memory.program_counter = nnn;
        break;
    case 0x20: //CALL addr
        memory.call(nnn);
        break;
    case 0x30: //SE Vx, byte
        if (memory.registers[x] == right_opcode) memory.program_counter += 2;
        break;
    case 0x40: //SNE Vx, byte
        if (memory.registers[x] != right_opcode) memory.program_counter += 2;
        break;
    case 0x50: //SE Vx, byte
        if (memory.registers[x] == memory.registers[y]) memory.program_counter += 2;
        break;
    case 0x60: //LD Vx, byte
        memory.registers[x] = right_opcode;
        break;
    case 0x70: //ADD Vx, byte
        memory.registers[x] += right_opcode;
    case 0x80:
        switch (right_opcode & 0x0F)
        {
        case 0x0: //LD Vx, Vy
            memory.registers[x] = memory.registers[y];
            break;
        case 0x1: //OR Vx, Vy
            memory.registers[x] = memory.registers[x] | memory.registers[y];
            break;
        case 0x2: //AND Vx, Vy
            memory.registers[x] = memory.registers[x] & memory.registers[y];
            break;
        case 0x3: //XOR Vx, Vy
            memory.registers[x] = memory.registers[x] ^ memory.registers[y];
            break;
        case 0x4: //ADD Vx, Vy
            memory.flag = memory.registers[x] + memory.registers[y] > 255;
            memory.registers[x] += memory.registers[y] & 0xFF;
            break;
        case 0x5: //SUB Vx, Vy
            memory.flag = memory.registers[x] > memory.registers[y];
            memory.registers[x] -= memory.registers[y];
            break;
        case 0x6: //SHR Vx
            memory.flag = (memory.registers[x] & 0x1) == 1;
            memory.registers[x] /= 2;
            break;
        case 0x7: //SUBN Vx, Vy
            memory.flag = memory.registers[y] > memory.registers[x];
            memory.registers[x] = memory.registers[y] - memory.registers[x];
            break;
        case 0xE: //SHL Vx
            memory.flag = (memory.registers[x] & 0x1) == 1;
            memory.registers[x] *= 2;
            break;

        default:
            throw std::invalid_argument(std::format("Wrong 0x80 opcode : {}", opcode));
        }
        break;

    case 0x90: //SNE Vx, Vy
        if (memory.registers[x] != memory.registers[y]) memory.program_counter += 2;
        break;
    case 0xA0: //LD I, addr
        memory.I = nnn;
        break;
    case 0xB0: //JP V0, addr
        memory.program_counter = nnn + memory.registers[0];
        break;
    case 0xC0: //RND Vx, byte TODO
        break;
    case 0xD0: //TODO
        break;
    case 0xE0: //TODO
        switch (right_opcode)
        {
        case 0x9E: //TODO
            break;
        case 0xA1: //TODO
            break;
        default:
            throw std::invalid_argument("Wrong 0xE0 opcode");
        }
        break;
    case 0xF0:
        switch (right_opcode)
        {
        case 0x07:
            memory.registers[x] = memory.delay_timer;
            break;
        case 0x0A: //wait a pressure
            break;
        case 0x15:
            memory.delay_timer = memory.registers[x];
            break;
        case 0x18:
            memory.sound_timer = memory.registers[x];
            break;
        case 0x1E:
            memory.I += memory.registers[x];
            break;
        case 0x29:
            //TODO
            break;
        case 0x33:
            //TODO
            break;
        case 0x55:
            for (int i = 0; i <= x; i++)
            {
                memory.memory[memory.I + i] = memory.registers[i];
            }
            break;
        case 0x65:
            for (int i = 0; i <= x; i++)
            {
                memory.registers[i] = memory.memory[memory.I + i];
            }
            break;
        default:
            throw std::invalid_argument("Wrong opcode 0xF0");
        }
        break;
    default:
        throw std::invalid_argument(std::format("Wrong opcode detected : {}", opcode));
    }
}
