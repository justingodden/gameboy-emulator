#pragma once

#include <array>
#include <stdint.h>

class Memory
{
public:
    Memory();
    ~Memory();

public:
    uint8_t readWRam(uint16_t addr);
    void writeWRam(uint16_t addr, uint8_t data);

    uint8_t readHRam(uint16_t addr);
    void writeHRam(uint16_t addr, uint8_t data);

private:
    std::array<uint8_t, 0x2000> wRam;            // work ram
    std::array<uint8_t, (0xFFFF - 0xFF80)> hRam; // high ram
};