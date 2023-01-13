#pragma once

#include <array>
#include <stdint.h>

class Ppu
{
public:
    Ppu();
    ~Ppu();

public:
    uint8_t readByte(uint16_t addr) const;
    void writeByte(uint16_t addr, uint8_t data);

private:
    std::array<uint8_t, 0x2000> vRam;
    std::array<std::array<std::array<uint8_t, 160>, 144>, 3> screenData;
};