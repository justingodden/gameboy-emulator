#include "Memory.h"

Memory::Memory()
{
    std::fill(wRam.begin(), wRam.end(), 0);
    std::fill(hRam.begin(), hRam.end(), 0);
}

Memory::~Memory()
{
}

uint8_t Memory::readWRam(uint16_t addr)
{
    return wRam[addr];
}

void Memory::writeWRam(uint16_t addr, uint8_t data)
{
    wRam[addr] = data;
}

uint8_t Memory::readHRam(uint16_t addr)
{
    return hRam[addr];
}

void Memory::writeHRam(uint16_t addr, uint8_t data)
{
    hRam[addr] = data;
}
