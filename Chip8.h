//
// Created by leroideskiwis on 10/01/25.
//

#ifndef CHIP8_H
#define CHIP8_H
#define START_ADDRESS 0x200
#include <string>

typedef unsigned char byte;
struct Memory {

    byte memory[4096]{};
    byte registers[16]{};
    byte stack[16]{};
    byte I{};
    byte flag{};

    byte delay_timer{};
    byte sound_timer{};

    int program_counter = START_ADDRESS;
    byte stack_pointer{};

    byte operator[](int i) const
    {
        return memory[i];
    }

    void call(int nnn)
    {
        stack_pointer++;
        stack[stack_pointer] = program_counter;
        program_counter = nnn;
    }

    void ret()
    {
        program_counter = stack[stack_pointer--];
    }
};

class Display
{
    bool pixels[32][64]{};
};

class Chip8
{
    Memory memory;
    Display display;
public:
    Chip8() = default;
    void load(const std::string& fileName);
    void tick();
    void process(byte left_opcode, byte right_opcode);

};


#endif //CHIP8_H
