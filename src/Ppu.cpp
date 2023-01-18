#include "Ppu.h"

Ppu::Ppu()
{
    std::fill(vRam.begin(), vRam.end(), 0);
}

Ppu::~Ppu()
{
}

uint8_t Ppu::readVRamByte(uint16_t addr) const
{
    return vRam[addr];
}

void Ppu::writeVRamByte(uint16_t addr, uint8_t data)
{
    vRam[addr] = data;
}

void Ppu::update(unsigned int cycles)
{
}