#pragma once

#include <array>
#include <stdint.h>

class Ppu
{
public:
    Ppu();
    ~Ppu();

public:
    uint8_t readVRamByte(uint16_t addr) const;
    void writeVRamByte(uint16_t addr, uint8_t data);
    void update(unsigned int cycles);

private:
    std::array<uint8_t, 0x2000> vRam;
    std::array<std::array<std::array<uint8_t, 160>, 144>, 3> screenData;
    uint8_t currentScanline = 0;
};