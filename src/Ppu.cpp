#include "Ppu.h"

Ppu::Ppu()
{
    std::fill(vRam.begin(), vRam.end(), 0);
}

Ppu::~Ppu()
{
}

uint8_t Ppu::readByte(uint16_t addr) const
{
    return vRam[addr];
}

void Ppu::writeByte(uint16_t addr, uint8_t data)
{
    vRam[addr] = data;
}
