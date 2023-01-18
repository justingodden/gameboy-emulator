#include "Memory.h"

Memory::Memory()
{
    std::fill(wRam.begin(), wRam.end(), 0);
    std::fill(hRam.begin(), hRam.end(), 0);
}

Memory::~Memory()
{
}

uint8_t Memory::readWRamByte(uint16_t addr)
{
    return wRam[addr];
}

void Memory::writeWRamByte(uint16_t addr, uint8_t data)
{
    wRam[addr] = data;
}

uint8_t Memory::readHRamByte(uint16_t addr)
{
    return hRam[addr];
}

void Memory::writeHRamByte(uint16_t addr, uint8_t data)
{
    hRam[addr] = data;
}
