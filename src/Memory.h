#pragma once

#include <array>
#include <stdint.h>

class Memory
{
public:
    Memory();
    ~Memory();

public:
    uint8_t readWRamByte(uint16_t addr);
    void writeWRamByte(uint16_t addr, uint8_t data);

    uint8_t readHRamByte(uint16_t addr);
    void writeHRamByte(uint16_t addr, uint8_t data);

private:
    std::array<uint8_t, 0x2000> wRam;                // work ram
    std::array<uint8_t, (0xFFFE - 0xFF80 + 1)> hRam; // high ram
};